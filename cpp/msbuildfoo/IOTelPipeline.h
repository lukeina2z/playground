#pragma once

#include <memory>
#include <string>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4996)
#endif

#include "opentelemetry/logs/provider.h"

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#include "opentelemetry/logs/logger.h"
#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/nostd/shared_ptr.h"
#include "opentelemetry/nostd/string_view.h"

#include "opentelemetry/trace/provider.h"
#include "opentelemetry/trace/scope.h"
#include "opentelemetry/trace/span.h"
#include "opentelemetry/trace/span_context.h"
#include "opentelemetry/trace/tracer.h"
#include "opentelemetry/trace/tracer_provider.h"
#include "opentelemetry/trace/span_id.h"
#include "opentelemetry/trace/trace_id.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"

namespace MsaLab { namespace Api
{
  struct IOTelPipeline
  {
  public:
    IOTelPipeline() = default;
    virtual ~IOTelPipeline() = default;

    virtual void Start() = 0;
    virtual void Shutdown() = 0;
  };

  std::unique_ptr<IOTelPipeline> CreateOTelPipeline(const std::string& name);
  std::unique_ptr<IOTelPipeline> CreateOTelPipelineWithOtlpExporter(const std::string& name);

  inline opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> GetTracer(const std::string& tracerName,
      const std::string& version = "")
  {
    auto provider = opentelemetry::trace::Provider::GetTracerProvider();
    return provider->GetTracer(tracerName, version);
  }

  inline opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> GetLogger(const std::string& loggerName,
    const std::string& version = "")
  {
    auto provider = opentelemetry::logs::Provider::GetLoggerProvider();
    return provider->GetLogger(loggerName, version);
  }

} // namespace Api
} // namespace MsaLab
