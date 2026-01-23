
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

  std::unique_ptr<opentelemetry::exporter::etw::TracerProvider> CreateGenevaTracerProvider()
  {
    return std::make_unique<opentelemetry::exporter::etw::TracerProvider>();
  }

} // namespace Details
} // namespace LkLab