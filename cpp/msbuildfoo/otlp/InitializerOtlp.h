#include "../common/OTelPipeline.h"

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

namespace MsaLab { namespace Details {
  std::unique_ptr<trace_sdk::TracerProvider> CreateOtlpTraceProvider(
  const std::string& serviceName);
} // namespace Details
} // namespace LkLab



