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

#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"

#include "../IOtelPipeline.h"
#include "GenevaTest.h"

namespace {
  const std::string serviceName = "LkLab-Foo-ETW";
  const std::string tracerName = "Geneva-Tracer-Foo";
  const std::string loggerName = "Geneva-Logger-Foo";
}

namespace MsaLab { namespace Details
{

  void TestLogWithGeneva()
  {
    auto otel = MsaLab::Api::CreateOTelPipeline(serviceName);
    otel->Start();

    auto tracer = MsaLab::Api::GetTracer(tracerName);
    auto logger = MsaLab::Api::GetLogger(loggerName);

    auto span = tracer->StartSpan("Test-Log-Main");
    auto scopeFoo = tracer->WithActiveSpan(span);

    logger->Fatal("Hello <Fatal> Otlp!");
    logger->Error("Hello <Error> Otlp!");
    logger->Info("Hello <Info> Otlp!");
    logger->Debug("Hello <Debug> Otlp!");

    auto ctx = tracer->GetCurrentSpan()->GetContext();
    // logger->Log(opentelemetry::logs::Severity::kError, "Hello <Current Span Context> Otlp!", ctx.trace_id(), ctx.span_id(), ctx.trace_flags());

    // otel->Shutdown();

    logger->Debug("xyz-body", ctx.trace_id(), ctx.span_id(), ctx.trace_flags());

    span->End();

    logger->Debug("xyzxyz - The end. No trace context expected.");
  }

void TestTraceWithGeneva()
{
  auto otelPipeline = MsaLab::Api::CreateOTelPipeline("OTel-Pipe-With-ETW");
  otelPipeline->Start();

  auto tracer = MsaLab::Api::GetTracer(tracerName);

  auto logger = MsaLab::Api::GetLogger(loggerName);

  auto fooEtw = tracer->StartSpan("main");
  auto scopefooEtw = tracer->WithActiveSpan(fooEtw);

  {
    // Create Span with 1 SpanLink
    auto barEtw = tracer->StartSpan(
      "child", opentelemetry::common::MakeAttributes({ {"key1", "value 1"}, {"key2", 1} }));

    barEtw->SetAttribute("attr_key1", 123);

    auto scopeBar = tracer->WithActiveSpan(barEtw);
    {
      // Create Span with 2 SpanLinks
      auto bazEtw = tracer->StartSpan(
        "grandchild", opentelemetry::common::MakeAttributes({ {"key3", "value 3"}, {"key4", 2} }));

      bazEtw->SetAttribute("attr_key2", 456);
      bazEtw->End();
    }

    barEtw->End();
  }

  fooEtw->End();

  logger->Info("Hello World Geneva!");
}

} // namespace Details
} // namespace MsaLab

