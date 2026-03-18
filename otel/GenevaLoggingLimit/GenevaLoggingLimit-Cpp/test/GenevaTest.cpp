#include <string>

#include "../IOtelPipeline.h"
#include "GenevaTest.h"
#include "test.h"

namespace {
  const std::string serviceName = "Geneva-Otlp-Test-App";
  //const std::string tracerName = "Geneva-Test-Library";
  //const std::string loggerName = tracerName;
  const std::string tracerName = "MSATraceV1";
  const std::string loggerName = "MSADataPointLogger";
}


namespace MsaLab { namespace Details
{

  void TestLogWithGeneva()
  {
    auto otel = MsaLab::Api::CreateOTelPipeline(serviceName);
    otel->Start();

    auto tracer = MsaLab::Api::GetTracer(tracerName);
    auto logger = MsaLab::Api::GetLogger(loggerName, "DatapointLogLib");

    // TestLog(logger, tracer);

    TestLogAttributeLimit(logger, tracer);

    otel->Shutdown();
  }

void TestTraceWithGeneva()
{
  auto otelPipeline = MsaLab::Api::CreateOTelPipeline("OTel-Pipe-With-ETW");
  otelPipeline->Start();

  auto tracer = MsaLab::Api::GetTracer(tracerName);
  auto logger = MsaLab::Api::GetLogger(loggerName, "DatapointLogLib");

  TestTrace(logger, tracer);
  otelPipeline->Shutdown();
}

} // namespace Details
} // namespace MsaLab

