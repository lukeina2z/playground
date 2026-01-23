#include "InitializerOtlp.h"

#include <memory>
#include <string>

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"

#include "opentelemetry/sdk/trace/tracer_context.h"
#include "opentelemetry/sdk/trace/tracer_context_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"
#include <opentelemetry/sdk/trace/simple_processor.h>
#include "opentelemetry/sdk/trace/simple_processor_factory.h"



#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http.h"
#include "opentelemetry/exporters/otlp/otlp_http_client.h"
#include <opentelemetry/exporters/otlp/otlp_http_exporter.h>
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"

#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"

namespace MsaLab { namespace Details {

  std::unique_ptr<logs_sdk::LoggerProvider> CreateOtlpLoggerProvider()
  {
    // Create ostream log exporter instance
    auto exporter =
      std::unique_ptr<logs_sdk::LogRecordExporter>(new logs_exporter::OStreamLogRecordExporter);
    auto processor = logs_sdk::SimpleLogRecordProcessorFactory::Create(std::move(exporter));

    return logs_sdk::LoggerProviderFactory::Create(std::move(processor));
  }

  std::unique_ptr<trace_sdk::TracerProvider> CreateOtlpTracerProvider(
    const std::string& serviceName)
  {
    const std::string ingestionSvc = "http://127.0.0.1:4318";

    opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;
    opts.url = ingestionSvc + "/v1/traces";
    opts.console_debug = true;

    opts.content_type = opentelemetry::exporter::otlp::HttpRequestContentType::kJson;
    // opts.content_type  = opentelemetry::exporter::otlp::HttpRequestContentType::kBinary;

    auto otlp_http_exporter = std::make_unique<opentelemetry::exporter::otlp::OtlpHttpExporter>(opts);
    auto otlp_http_processor = std::make_unique<opentelemetry::sdk::trace::SimpleSpanProcessor>(
      std::move(otlp_http_exporter));

    auto ostream_exporter = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();

    opentelemetry::sdk::trace::BatchSpanProcessorOptions options;
    options.max_queue_size = 10;
    options.schedule_delay_millis = std::chrono::milliseconds(3000);
    options.max_export_batch_size = 3;

    auto ostream_processor = std::make_unique<opentelemetry::sdk::trace::BatchSpanProcessor>(
      std::move(ostream_exporter), options);
    // auto ostream_processor =
    // opentelemetry::sdk::trace::SimpleSpanProcessorFactory::Create(std::move(ostream_exporter));

    std::vector<std::unique_ptr<opentelemetry::sdk::trace::SpanProcessor>> processors;
    processors.push_back(std::move(ostream_processor));
    processors.push_back(std::move(otlp_http_processor));

    auto resource_attributes =
      opentelemetry::sdk::resource::ResourceAttributes{ {"service.name", serviceName} };
    auto resource_ptr = opentelemetry::sdk::resource::Resource::Create(resource_attributes);

    // Default is an always-on sampler.
    std::unique_ptr<opentelemetry::sdk::trace::TracerContext> context =
      opentelemetry::sdk::trace::TracerContextFactory::Create(std::move(processors), resource_ptr);

    auto sdk_provider = opentelemetry::sdk::trace::TracerProviderFactory::Create(std::move(context));

    return sdk_provider;
  }
} // namespace Details
} // namespace LkLab