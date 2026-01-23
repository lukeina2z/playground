#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

namespace MsaLab { namespace Details {
opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider> CreateOtlpTraceProvider(
  const std::string& serviceName);
} // namespace Details
} // namespace LkLab



