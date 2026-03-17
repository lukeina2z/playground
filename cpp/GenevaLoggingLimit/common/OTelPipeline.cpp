#include <memory>
#include <string>

#include "../IOTelPipeline.h"
#include "../geneva/otelgeneva.h"
#include "../otlp/otelotlp.h"

namespace MsaLab { namespace Api
{
  std::unique_ptr<IOTelPipeline> CreateOTelPipeline(const std::string& name)
  {
    return std::make_unique<MsaLab::Details::OTelPipelineGeneva>(name);
  }

  std::unique_ptr<IOTelPipeline> CreateOTelPipelineWithOtlpExporter(const std::string& name)
  {
    return std::make_unique<MsaLab::Details::OTelPipelineOtlp>(name);
  }

} // namespace Api
} // namespace MsaLab