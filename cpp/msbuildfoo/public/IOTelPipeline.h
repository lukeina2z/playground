#pragma once

#include <memory>
#include <string>

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

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
} // namespace Api
} // namespace MsaLab
