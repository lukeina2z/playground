
#include <map>
#include <string>
#include <vector>

#include "opentelemetry/trace/span_context.h"

#include "../IOtelPipeline.h"
#include "OtlpTest.h"
#include "test.h"

namespace {
  const std::string serviceName = "MsaLab-Foo-Otlp";
  const std::string tracerName = "Otlp-Tracer-Foo";
  const std::string loggerName = "Otlp-Logger-Foo";
}

namespace MsaLab { namespace Details
{
  const char* kGlobalProviderName = "OpenTelemetry-ETW-TLD-Geneva-Example";
  std::string providerName = kGlobalProviderName;

  using L = std::vector<std::pair<opentelemetry::trace::SpanContext, std::map<std::string, std::string>>>;

} // namespace Details
} // namespace MsaLab





