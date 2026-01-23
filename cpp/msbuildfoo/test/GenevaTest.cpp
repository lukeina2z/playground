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

#include "../public/IOtelPipeline.h"
#include "GenevaTest.h"

namespace MsaLab { namespace Details
{
void TestTraceWithGeneva()
{
  const std::string serviceName = "LkLab-Foo-ETW";
  auto otelPipeline = MsaLab::Api::CreateOTelPipeline("OTel-Pipe-With-ETW");
  otelPipeline->Start();

  const std::string tracerName = "InstrScope-Main-ETW";
  auto tracer = MsaLab::Api::GetTracer(tracerName);

  // auto logger = InitLogger();

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

  // logger->Info("Hello World ETW!");
}

} // namespace Details
} // namespace MsaLab

