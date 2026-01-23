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

#include "../otlp/InitializerOtlp.h"

namespace MsaLab { namespace Details
{
  //namespace logs_api = opentelemetry::logs;
  //namespace logs_sdk = opentelemetry::sdk::logs;
  // namespace logs_exporter = opentelemetry::exporter::logs;

  namespace trace_api = opentelemetry::trace;
  namespace trace_sdk = opentelemetry::sdk::trace;
  namespace trace_exporter = opentelemetry::exporter::trace;

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

  void OTelPipelineOtlp::InitLogger()
  {
    m_loggerProvider = CreateOtlpLoggerProvider();

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
    if (m_tracerProvider)
    {
      m_tracerProvider->ForceFlush();
    }

    m_tracerProvider.reset();
    std::shared_ptr<opentelemetry::trace::TracerProvider> none;
    trace_sdk::Provider::SetTracerProvider(none);
    std::shared_ptr<trace_api::TracerProvider> noop;
    trace_sdk::Provider::SetTracerProvider(noop);
  }


  void OTelPipelineOtlp::CleanupTracer()
  {
    // We call ForceFlush to prevent to cancel running exportings, It's optional.
    if (m_tracerProvider)
    {
      m_tracerProvider->ForceFlush();
    }

    m_tracerProvider.reset();
    std::shared_ptr<opentelemetry::trace::TracerProvider> none;
    trace_sdk::Provider::SetTracerProvider(none);
    std::shared_ptr<trace_api::TracerProvider> noop;
    trace_sdk::Provider::SetTracerProvider(noop);
  }



  void OTelPipelineOtlp::Shutdown()
  {
    std::shared_ptr<opentelemetry::trace::TracerProvider> nullPtr;
    trace_api::Provider::SetTracerProvider(std::move(nullPtr));
  }

} // namespace Details
} // namespace MsaLab
