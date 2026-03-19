
#include <map>
#include <string>
#include <vector>

#include "opentelemetry/common/key_value_iterable_view.h"
#include "opentelemetry/logs/logger.h"
#include "opentelemetry/nostd/shared_ptr.h"
#include "opentelemetry/trace/span_context.h"
#include "opentelemetry/trace/tracer.h"

#include "../IOtelPipeline.h"
#include "../common/common.h"
#include "OtlpTest.h"


namespace MsaLab { namespace Details
{
  using L = std::vector<std::pair<opentelemetry::trace::SpanContext, std::map<std::string, std::string>>>;


  static std::vector<std::pair<std::string, opentelemetry::common::AttributeValue>> BuildTestData()
  {
      constexpr int kTestAttributeCount = 300;

      // Keep value strings alive in a static vector so that the const char*
      // pointers stored inside AttributeValue remain valid.
      static std::vector<std::string> ownedValues;
      ownedValues.clear();
      ownedValues.reserve(kTestAttributeCount);

      std::vector<std::pair<std::string, opentelemetry::common::AttributeValue>> testData;
      testData.reserve(kTestAttributeCount);

      // Use short keys/values to stay well under the 64KB ETW event size limit
      // so we isolate the attribute-count limit (128 EVENT_DATA_DESCRIPTORs).
      for (int i = 0; i < kTestAttributeCount; ++i)
      {
          std::string key = "K" + std::to_string(i);
          ownedValues.emplace_back("V" + std::to_string(i));
          const char* val = ownedValues.back().c_str();
          testData.emplace_back(std::move(key), val);
      }
      return testData;
  }


  void TestLogAttributeLimit(opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger>& logger,
      opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer>& tracer)
  {

      std::vector<std::pair<std::string, opentelemetry::common::AttributeValue>> processedAttrVec = BuildTestData(); // For testing, replace with real data point attributes when available.

      auto attrView = opentelemetry::common::MakeKeyValueIterableView(processedAttrVec);
      const opentelemetry::common::KeyValueIterable& attrIterable = attrView;
      logger->Info("GenevaLogAttributeLimitTest-Cpp", attrIterable);

  }

  void TestLog(opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger>& logger,
    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer>& tracer)
  {
    trace_api::StartSpanOptions options;
    options.kind = trace_api::SpanKind::kServer;
    auto span = tracer->StartSpan("Test-Log-Main-Span", options);
    {
      auto scopeFoo = tracer->WithActiveSpan(span);

      logger->Fatal("Hello <Fatal> Otlp!");
      logger->Error("Hello <Error> Otlp!");

      const logs_api::EventId process_request_event_id{ 0x12345678 /* event ID value */, "Company.Component.SubComponent.FunctionName" /* event name */ };

      logger->Info(process_request_event_id, "Info message from {pid}", opentelemetry::common::MakeAttributes({ {"pid", 12347} }));
      logger->Error(process_request_event_id, "Error message from {pid}", opentelemetry::common::MakeAttributes({ {"pid", 12347} }));


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
    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer>& tracer)
  {
    logger->Info("Inside TestTrace, Before span creation.");
    trace_api::StartSpanOptions options;
    options.kind = trace_api::SpanKind::kServer;
    auto s1 = tracer->StartSpan("Test-Trace-Main-Span", options);
    auto scopeFoo = tracer->WithActiveSpan(s1);

    {
      L link1 = { {s1->GetContext(), {}} };
      {
        trace_api::StartSpanOptions optionsS2;
        optionsS2.kind = trace_api::SpanKind::kClient;
        
        // Create Span with 1 SpanLink
        auto s2 = tracer->StartSpan(
          "Child-Span", opentelemetry::common::MakeAttributes({ {"key1", "value 1"}, {"key2", 1} }), link1, optionsS2);

        s2->SetAttribute("attr_key1", 123);

        auto scopeBar = tracer->WithActiveSpan(s2);
        {
          L link2 = { {s1->GetContext(), {}}, {s2->GetContext(), {}} };

          trace_api::StartSpanOptions optionsS3;
          optionsS3.kind = trace_api::SpanKind::kServer;
          // Create Span with 2 SpanLinks
          auto s3 = tracer->StartSpan(
            "Grandchild-Span",
            opentelemetry::common::MakeAttributes({ {"key3", "value 3"}, {"key4", 2} }),
            link2,
            optionsS3);

          s3->SetAttribute("attr_key2", 456);

          logger->Info("Inside Child-Span Scope : Test Log API!");

          s3->End();
        }

        s2->AddEvent("An event in Child-Span", opentelemetry::common::SystemTimestamp(std::chrono::system_clock::now()),
          opentelemetry::common::MakeAttributes({ {"event_attr1", "event value 1"} }));

        s2->End();
      }
    }
    s1->End();

    // tracer->CloseWithMicroseconds(3000);
    // otel->Shutdown();

    //auto endOne = tracer->StartSpan("after-end-one");
    //auto scopeEnd = tracer->WithActiveSpan(endOne);
    //endOne->End();
    //logger->Info("Inside <TestTraceWithOtlp> : The End!");
  }

} // namespace Details
} // namespace MsaLab





