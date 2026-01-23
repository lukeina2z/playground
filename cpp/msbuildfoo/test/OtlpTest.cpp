
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
#include "OtlpTest.h"

namespace MsaLab { namespace Details
{
  const char* kGlobalProviderName = "OpenTelemetry-ETW-TLD-Geneva-Example";
  std::string providerName = kGlobalProviderName;

  using L = std::vector<std::pair<trace_api::SpanContext, std::map<std::string, std::string>>>;

  void TestTraceWithOtlp()
  {
    const std::string serviceName = "MsBuild-Foo-OTLP";
    auto otel = MsaLab::Api::CreateOTelPipelineWithOtlpExporter(serviceName);
    otel->Start();

    const std::string tracerName = "InstrScope-msbuildfoo-Otlp";
    auto tracer = MsaLab::Api::GetTracer(tracerName);

    // auto logger = InitLogger();

    auto s1 = tracer->StartSpan("main");
    auto scopeFoo = tracer->WithActiveSpan(s1);

    {
      L link1 = { {s1->GetContext(), {}} };

      // Create Span with 1 SpanLink
      auto s2 = tracer->StartSpan(
        "child", opentelemetry::common::MakeAttributes({ {"key1", "value 1"}, {"key2", 1} }), link1);

      s2->SetAttribute("attr_key1", 123);

      auto scopeBar = tracer->WithActiveSpan(s2);
      {
        L link2 = { {s1->GetContext(), {}}, {s2->GetContext(), {}} };

        // Create Span with 2 SpanLinks
        auto s3 = tracer->StartSpan(
          "grandchild", opentelemetry::common::MakeAttributes({ {"key3", "value 3"}, {"key4", 2} }),
          link2);

        s3->SetAttribute("attr_key2", 456);

        s3->End();
      }

      s2->End();
    }

    s1->End();

    // logger->Info("Hello World!");
  }
} // namespace Details
} // namespace MsaLab





