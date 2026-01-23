#include "otelotlp.h"

#include <memory>
#include <string>

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/common/global_log_handler.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/logs/batch_log_record_processor.h"
#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"


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

#include "opentelemetry/exporters/otlp/otlp_environment.h"
#include "opentelemetry/exporters/otlp/otlp_http.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/exporters/otlp/otlp_http_log_record_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_log_record_exporter_options.h"

#include "opentelemetry/exporters/ostream/log_record_exporter.h"

namespace MsaLab { namespace Details
{
  const std::string kOtlpGrpcServer = "http://127.0.0.1:4317";
  const std::string kOtlpHttpServer = "http://127.0.0.1:4318";
  const std::string kOtlpHttpLogsEndpoint = kOtlpHttpServer + "/v1/logs";
  const std::string kOtlpHttpTracesEndpoint = kOtlpHttpServer + "/v1/traces";

  std::unique_ptr<logs_sdk::LoggerProvider> CreateOtlpLoggerProvider(const std::string& serviceName)
  {
    opentelemetry::exporter::otlp::OtlpHttpLogRecordExporterOptions logger_opts;
    logger_opts.url = kOtlpHttpLogsEndpoint;
    logger_opts.console_debug = false;

    std::vector<std::unique_ptr<logs_sdk::LogRecordProcessor>> processors;

    auto otlp_exporter = otlp::OtlpHttpLogRecordExporterFactory::Create(logger_opts);
    logs_sdk::BatchLogRecordProcessorOptions batch_opts;
    //processors.push_back(std::unique_ptr<logs_sdk::LogRecordProcessor>(
    //  new logs_sdk::BatchLogRecordProcessor(std::move(otlp_exporter), batch_opts)));

    auto ostream_exporter = std::unique_ptr<logs_sdk::LogRecordExporter>(
      new logs_exporter::OStreamLogRecordExporter);
    processors.push_back(
      logs_sdk::SimpleLogRecordProcessorFactory::Create(std::move(ostream_exporter)));

    auto resource_attributes = opentelemetry::sdk::resource::ResourceAttributes{ {"service.name", serviceName} };
    auto resource = opentelemetry::sdk::resource::Resource::Create(resource_attributes);

    return logs_sdk::LoggerProviderFactory::Create(std::move(processors), resource);
  }

  std::unique_ptr<trace_sdk::TracerProvider> CreateOtlpTracerProvider(
    const std::string& serviceName)
  {
    opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;
    opts.url = kOtlpHttpTracesEndpoint;
    opts.console_debug = false;

    opts.content_type = opentelemetry::exporter::otlp::HttpRequestContentType::kJson;
    // opts.content_type  = opentelemetry::exporter::otlp::HttpRequestContentType::kBinary;

    opentelemetry::sdk::trace::BatchSpanProcessorOptions batchOption;
    batchOption.max_queue_size = 10;
    batchOption.schedule_delay_millis = std::chrono::milliseconds(3000);
    batchOption.max_export_batch_size = 3;

    auto otlp_http_exporter = std::make_unique<opentelemetry::exporter::otlp::OtlpHttpExporter>(opts);
    //auto otlp_http_processor = std::make_unique<opentelemetry::sdk::trace::SimpleSpanProcessorFactory>(
    //  std::move(otlp_http_exporter));
    auto otlp_http_processor = std::make_unique<opentelemetry::sdk::trace::BatchSpanProcessor>(
      std::move(otlp_http_exporter), batchOption);

    auto ostream_exporter = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();

    //auto ostream_processor = std::make_unique<opentelemetry::sdk::trace::BatchSpanProcessor>(
    //  std::move(ostream_exporter), batchOption);
    auto ostream_processor =
      opentelemetry::sdk::trace::SimpleSpanProcessorFactory::Create(std::move(ostream_exporter));

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

  OTelPipelineOtlp::OTelPipelineOtlp(const std::string& serviceName, bool useGenevaExporter)
    : m_serviceName(serviceName)
  {
  }

  OTelPipelineOtlp::~OTelPipelineOtlp()
  {
    Shutdown();
  }

  void OTelPipelineOtlp::Start()
  {
    InitLogger();
    InitTracer();
  }

  void OTelPipelineOtlp::Shutdown()
  {
    CleanupLogger();
    CleanupTracer();
  }

  void OTelPipelineOtlp::InitLogger()
  {
    m_loggerProvider = CreateOtlpLoggerProvider(m_serviceName);

    // Set the global logger provider
    const std::shared_ptr<logs_api::LoggerProvider>& api_provider = m_loggerProvider;
    logs_sdk::Provider::SetLoggerProvider(api_provider);
  }

  void OTelPipelineOtlp::InitTracer()
  {
    m_tracerProvider = CreateOtlpTracerProvider(m_serviceName);

    // Set the global trace provider
    std::shared_ptr<trace_api::TracerProvider> api_provider = m_tracerProvider;
    opentelemetry::sdk::trace::Provider::SetTracerProvider(std::move(api_provider));

    // set global propagator
    auto pHttpTraceContext = new opentelemetry::trace::propagation::HttpTraceContext();
    opentelemetry::context::propagation::GlobalTextMapPropagator::SetGlobalPropagator(
      opentelemetry::nostd::shared_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        pHttpTraceContext));
  }

  void OTelPipelineOtlp::CleanupLogger()
  {
    // We call ForceFlush to prevent to cancel running exportings, It's optional.
    if (m_loggerProvider)
    {
      m_loggerProvider->ForceFlush();
    }

    m_loggerProvider.reset();
    std::shared_ptr<logs_api::LoggerProvider> noop;
    logs_sdk::Provider::SetLoggerProvider(noop);
  }

  void OTelPipelineOtlp::CleanupTracer()
  {
    // We call ForceFlush to prevent to cancel running exportings, It's optional.
    if (m_tracerProvider)
    {
      m_tracerProvider->ForceFlush();
    }

    m_tracerProvider.reset();
    std::shared_ptr<trace_api::TracerProvider> noop;
    trace_sdk::Provider::SetTracerProvider(noop);
  }

} // namespace Details
} // namespace MsaLab
