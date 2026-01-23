#include <memory>
#include <string>

#include "../IOTelPipeline.h"
#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"

namespace MsaLab { namespace Details
{
  std::unique_ptr<opentelemetry::exporter::etw::LoggerProvider> CreateGenevaLoggerProvider();

  std::unique_ptr<opentelemetry::exporter::etw::TracerProvider> CreateGenevaTracerProvider();

  class OTelPipelineGeneva : public MsaLab::Api::IOTelPipeline
  {
  public:
    OTelPipelineGeneva(const std::string& serviceName);
    virtual ~OTelPipelineGeneva();

    virtual void Start() override;
    virtual void Shutdown() override;

  protected:
    void InitLogger();
    void InitTracer();

    void CleanupLogger();
    void CleanupTracer();

  private:
    std::shared_ptr<opentelemetry::exporter::etw::LoggerProvider> m_loggerProvider;
    std::shared_ptr<opentelemetry::exporter::etw::TracerProvider> m_tracerProvider;
    std::string m_serviceName = "";
  };

} // namespace Details
} // namespace MsaTel

