
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

  using L = std::vector<std::pair<trace_api::SpanContext, std::map<std::string, std::string>>>;

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





