
#include <map>
#include <string>
#include <vector>

#include "opentelemetry/common/key_value_iterable_view.h"
#include "opentelemetry/logs/logger.h"
#include "opentelemetry/nostd/shared_ptr.h"
#include "opentelemetry/trace/span_context.h"
#include "opentelemetry/trace/tracer.h"

#include "../IOtelPipeline.h"
#include "OtlpTest.h"


namespace MsaLab { namespace Details
{
  using L = std::vector<std::pair<opentelemetry::trace::SpanContext, std::map<std::string, std::string>>>;

  void TestLog(opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger>& logger,
    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> tracer)
  {
    auto span = tracer->StartSpan("Test-Log-Main-Span");
    {
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
    }
    logger->Debug("xyzxyz - The end. No trace context expected.");
  }

  void TestTrace(opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger>& logger,
    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> tracer)
  {
    logger->Info("Inside <TestTraceWithOtlp>, Before span creation : Hello World!");
    auto s1 = tracer->StartSpan("Test-Trace-Main-Span");
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

    // tracer->CloseWithMicroseconds(3000);
    // otel->Shutdown();

    auto endOne = tracer->StartSpan("after-end-one");
    auto scopeEnd = tracer->WithActiveSpan(endOne);
    endOne->End();
    logger->Info("Inside <TestTraceWithOtlp> : The End!");
  }

} // namespace Details
} // namespace MsaLab





