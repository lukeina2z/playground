#include <memory>
#include <string>

#include "../IOTelPipeline.h"
#include "../geneva/otelgeneva.h"

namespace MsaLab { namespace Api
{
  std::unique_ptr<IOTelPipeline> CreateOTelPipeline(const std::string& name)
  {
    return std::make_unique<MsaLab::Details::OTelPipelineGeneva>(name);
  }

} // namespace Api
} // namespace MsaLab