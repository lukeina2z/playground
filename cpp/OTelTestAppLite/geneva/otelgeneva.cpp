#include "otelgeneva.h"

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"
#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"

namespace logs_api = opentelemetry::logs;
namespace logs_sdk = opentelemetry::sdk::logs;

namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;


namespace MsaLab { namespace Details
{

  std::unique_ptr<opentelemetry::exporter::etw::LoggerProvider> CreateGenevaLoggerProvider()
  {

    static std::map<std::string, std::string> tableNameMappings = { {"libFoo", "logTableFoo"}, {"libBar", "logTableBar"} };
    opentelemetry::exporter::etw::TelemetryProviderOptions options = { {"enableTableNameMappings", true},
                                                            {"tableNameMappings", tableNameMappings} };

    return std::make_unique<opentelemetry::exporter::etw::LoggerProvider>(options);
  }

  std::unique_ptr<opentelemetry::exporter::etw::TracerProvider> CreateGenevaTracerProvider()
  {
    return std::make_unique<opentelemetry::exporter::etw::TracerProvider>();
  }

  OTelPipelineGeneva::OTelPipelineGeneva(const std::string& serviceName) : m_serviceName(serviceName)
  {
  }

  OTelPipelineGeneva::~OTelPipelineGeneva()
  {
    Shutdown();
  }

  //void TestEtwTracer()
  //{
  //  auto traceProvider = std::make_unique<opentelemetry::exporter::etw::TracerProvider>();
  //  auto tracer = traceProvider->GetTracer("Geneva-Tracer-Foo");

  //  {
  //    auto spanFoo = tracer->StartSpan("Span-Foo");
  //    spanFoo->AddEvent("FooEvent", opentelemetry::common::MakeAttributes({{"foo_key", "foo_value"}}));
  //  }
  //}


  void TestEtwTracer()
  {
    auto traceProvider = std::make_unique<opentelemetry::exporter::etw::TracerProvider>();
    auto tracer = traceProvider->GetTracer("Geneva-Tracer-Foo");
    auto spanFoo = tracer->StartSpan("Span-Foo");
    tracer = traceProvider->GetTracer("Geneva-Tracer-Bar");
    auto spanBar = tracer->StartSpan("Span-Bar");
    spanFoo->End();
    spanBar->End();
  }

  void OTelPipelineGeneva::Start()
  {
    InitLogger();
    InitTracer();

    TestEtwTracer();
  }

  void OTelPipelineGeneva::InitLogger()
  {
    m_loggerProvider = CreateGenevaLoggerProvider();

    // Set the global Logger provider
    std::shared_ptr<logs_api::LoggerProvider> api_provider = m_loggerProvider;
    opentelemetry::sdk::logs::Provider::SetLoggerProvider(std::move(api_provider));
  }

  void OTelPipelineGeneva::InitTracer()
  {
    m_tracerProvider = CreateGenevaTracerProvider();

    // Set the global trace provider
    std::shared_ptr<trace_api::TracerProvider> api_provider = m_tracerProvider;
    opentelemetry::sdk::trace::Provider::SetTracerProvider(std::move(api_provider));

    // set global propagator
    auto pHttpTraceContext = new opentelemetry::trace::propagation::HttpTraceContext();
    opentelemetry::context::propagation::GlobalTextMapPropagator::SetGlobalPropagator(
      opentelemetry::nostd::shared_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        pHttpTraceContext));
  }

  void OTelPipelineGeneva::CleanupLogger()
  {
    // We call ForceFlush to prevent to cancel running exportings, It's optional.
    if (m_loggerProvider)
    {
      // m_loggerProvider->ForceFlush();
    }

    m_loggerProvider.reset();
    std::shared_ptr<logs_api::LoggerProvider> noop;
    logs_sdk::Provider::SetLoggerProvider(noop);
  }

  void OTelPipelineGeneva::CleanupTracer()
  {
    // We call ForceFlush to prevent to cancel running exportings, It's optional.
    if (m_tracerProvider)
    {
      // m_tracerProvider->ForceFlush();
    }

    m_tracerProvider.reset();
    std::shared_ptr<opentelemetry::trace::TracerProvider> none;
    trace_sdk::Provider::SetTracerProvider(none);
    std::shared_ptr<trace_api::TracerProvider> noop;
    trace_sdk::Provider::SetTracerProvider(noop);
  }

  void OTelPipelineGeneva::Shutdown()
  {
    CleanupLogger();
    CleanupTracer();
  }

} // namespace Details
} // namespace MsaLab
