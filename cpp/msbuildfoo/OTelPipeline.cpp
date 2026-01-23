#include "OTelPipeline.h"

#include <memory>
#include <string>

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

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http.h"
#include "opentelemetry/exporters/otlp/otlp_http_client.h"
#include <opentelemetry/exporters/otlp/otlp_http_exporter.h>
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"

#include "initializer_geneva/InitializerGeneva.h"
#include "initializer_otlp/InitializerOtlp.h"

namespace MsaLab { namespace Details
{
  namespace trace_api = opentelemetry::trace;
  namespace trace_sdk = opentelemetry::sdk::trace;
  namespace trace_exporter = opentelemetry::exporter::trace;

  OTelPipeline::OTelPipeline(const std::string& serviceName, bool useGenevaExporter)
    : m_serviceName(serviceName), m_useGenevaExporter(useGenevaExporter)
  {
  }

  OTelPipeline::~OTelPipeline()
  {
    Shutdown();
  }

  void OTelPipeline::Start()
  {
    if (m_useGenevaExporter)
    {
      m_traceProvider = CreateGenevaTraceProvider(m_serviceName);
    }
    else
    {
      m_traceProvider = CreateOtlpTraceProvider(m_serviceName);
    }

    // Set the global trace provider
    opentelemetry::sdk::trace::Provider::SetTracerProvider(m_traceProvider);

    // set global propagator
    auto pHttpTraceContext = new opentelemetry::trace::propagation::HttpTraceContext();
    opentelemetry::context::propagation::GlobalTextMapPropagator::SetGlobalPropagator(
      opentelemetry::nostd::shared_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        pHttpTraceContext));
  }

  void OTelPipeline::Shutdown()
  {
    std::shared_ptr<opentelemetry::trace::TracerProvider> nullPtr;
    trace_api::Provider::SetTracerProvider(std::move(nullPtr));
  }

} // namespace Details
} // namespace MsaLab

namespace MsaLab { namespace Api
{
  std::unique_ptr<IOTelPipeline> CreateOTelPipeline(const std::string& name)
  {
    return std::make_unique<MsaLab::Details::OTelPipeline>(name, true);
  }

  std::unique_ptr<IOTelPipeline> CreateOTelPipelineWithOtlpExporter(const std::string& name)
  {
    return std::make_unique<MsaLab::Details::OTelPipeline>(name, false);
  }

} // namespace Api
} // namespace MsaLab