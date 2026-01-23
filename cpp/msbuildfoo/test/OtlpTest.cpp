
#include <map>
#include <string>
#include <vector>

#include "opentelemetry/trace/span_context.h"

#include "../IOtelPipeline.h"
#include "OtlpTest.h"
#include "test.h"

namespace {
  const std::string serviceName = "LkLab-Foo-Otlp";
  const std::string tracerName = "Otlp-Tracer-Foo";
  const std::string loggerName = "Otlp-Logger-Foo";
}

namespace MsaLab { namespace Details
{
  const char* kGlobalProviderName = "OpenTelemetry-ETW-TLD-Geneva-Example";
  std::string providerName = kGlobalProviderName;

  using L = std::vector<std::pair<opentelemetry::trace::SpanContext, std::map<std::string, std::string>>>;

  void TestTraceWithOtlp()
  {
    const std::string serviceName = "MsaLab-Foo-OTLP";
    auto otel = MsaLab::Api::CreateOTelPipelineWithOtlpExporter(serviceName);
    otel->Start();

    const std::string tracerName = "InstrScope-msalabfoo-Otlp";
    auto tracer = MsaLab::Api::GetTracer(tracerName);
    auto logger = MsaLab::Api::GetLogger(loggerName);
    TestTrace(logger, tracer);

    otel->Shutdown();
  }

  void TestLogWithOtlp()
  {
    auto otel = MsaLab::Api::CreateOTelPipelineWithOtlpExporter(serviceName);
    otel->Start();

    auto tracer = MsaLab::Api::GetTracer(tracerName);
    auto logger = MsaLab::Api::GetLogger(loggerName);
    TestLog(logger, tracer);

    otel->Shutdown();
  }

} // namespace Details
} // namespace MsaLab





