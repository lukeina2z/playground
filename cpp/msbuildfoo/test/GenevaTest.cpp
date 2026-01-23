#include <string>

#include "../IOtelPipeline.h"
#include "GenevaTest.h"
#include "test.h"

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
    TestLog(logger, tracer);
    otel->Shutdown();
  }

void TestTraceWithGeneva()
{
  auto otelPipeline = MsaLab::Api::CreateOTelPipeline("OTel-Pipe-With-ETW");
  otelPipeline->Start();

  auto tracer = MsaLab::Api::GetTracer(tracerName);
  auto logger = MsaLab::Api::GetLogger(loggerName);

  TestLog(logger, tracer);
  otelPipeline->Shutdown();
}

} // namespace Details
} // namespace MsaLab

