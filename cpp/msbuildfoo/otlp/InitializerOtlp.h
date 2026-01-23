#include "../common/common.h"

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/sdk/logs/logger_provider.h"

namespace MsaLab { namespace Details {

  std::unique_ptr<logs_sdk::LoggerProvider> CreateOtlpLoggerProvider();

  std::unique_ptr<trace_sdk::TracerProvider> CreateOtlpTracerProvider(
  const std::string& serviceName);

} // namespace Details
} // namespace LkLab



