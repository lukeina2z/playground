
#include "InitializerGeneva.h"

#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"



namespace
{

  const char* kGlobalProviderName = "OpenTelemetry-ETW-TLD-Geneva-Example";
  std::string providerName = kGlobalProviderName;

  using L = std::vector<std::pair<trace_api::SpanContext, std::map<std::string, std::string>>>;


  auto InitLogger()
  {
    static opentelemetry::exporter::etw::LoggerProvider logger_provider;
    // auto logger = logger_provider.GetLogger(providerName, "1.0");
    auto logger = logger_provider.GetLogger(std::string(providerName) + "-Logger", "1.0");
    return logger;
  }
}





namespace MsaLab { namespace Details {

  opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider> CreateGenevaTraceProvider(const std::string& serviceName)
  {
    auto etw_provider = std::make_shared<opentelemetry::exporter::etw::TracerProvider>();
    std::shared_ptr<opentelemetry::trace::TracerProvider> shared_provider =
      std::static_pointer_cast<opentelemetry::trace::TracerProvider>(etw_provider);

    opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider> spProvider{ shared_provider };

    return spProvider;
  }

} // namespace Details
} // namespace LkLab