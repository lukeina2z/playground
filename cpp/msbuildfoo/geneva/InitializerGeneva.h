
#include "../common/common.h"

#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"

namespace MsaLab { namespace Details {

  std::unique_ptr<opentelemetry::exporter::etw::LoggerProvider> CreateGenevaLoggerProvider();
  std::unique_ptr<opentelemetry::exporter::etw::TracerProvider> CreateGenevaTracerProvider();

} // namespace Details
} // namespace LkLab