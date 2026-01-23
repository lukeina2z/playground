#include <memory>
#include <string>

#include "../IOTelPipeline.h"
#include "opentelemetry/sdk/logs/logger_provider.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
namespace logs_sdk = opentelemetry::sdk::logs;
namespace trace_sdk = opentelemetry::sdk::trace;

namespace MsaLab { namespace Details
{
  std::unique_ptr<logs_sdk::LoggerProvider> CreateOtlpLoggerProvider(const std::string& serviceName);

  std::unique_ptr<trace_sdk::TracerProvider> CreateOtlpTracerProvider(
    const std::string& serviceName);

  class OTelPipelineOtlp : public MsaLab::Api::IOTelPipeline
  {
  public:
    OTelPipelineOtlp(const std::string& serviceName, bool useGenevaExporter = false);
    virtual ~OTelPipelineOtlp();

    virtual void Start() override;
    virtual void Shutdown() override;

  protected:
    void InitLogger();
    void InitTracer();

    void CleanupLogger();
    void CleanupTracer();

  private:
    std::shared_ptr<logs_sdk::LoggerProvider> m_loggerProvider;
    std::shared_ptr<trace_sdk::TracerProvider> m_tracerProvider;
    std::string m_serviceName = "";
  };

} // namespace Details
} // namespace MsaLab

