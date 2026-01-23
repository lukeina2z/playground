#pragma once

#include <memory>
#include <string>

namespace MsaLab { namespace Api
{
  struct IOTelPipeline
  {
  public:
    IOTelPipeline() = default;
    virtual ~IOTelPipeline() = default;

    virtual void Start() = 0;
    virtual void Close() = 0;
  };

  std::unique_ptr<IOTelPipeline> CreateOTelPipeline(const std::string& name);
  std::unique_ptr<IOTelPipeline> CreateOTelPipelineWithOtlpExporter(const std::string& name);
} // namespace Api
} // namespace MsaLab
