#include <memory>
#include <string>

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"

#include "opentelemetry/sdk/trace/tracer_context.h"
#include "opentelemetry/sdk/trace/tracer_context_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"
#include <opentelemetry/sdk/trace/simple_processor.h>
#include "opentelemetry/sdk/trace/simple_processor_factory.h"

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http.h"
#include "opentelemetry/exporters/otlp/otlp_http_client.h"
#include <opentelemetry/exporters/otlp/otlp_http_exporter.h>
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"

#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"

namespace MsaLab
{
  namespace trace_api = opentelemetry::trace;
  namespace trace_sdk = opentelemetry::sdk::trace;
  namespace trace_exporter = opentelemetry::exporter::trace;

  class OTelRuntime
  {
  public:
    OTelRuntime(const std::string& serviceName, bool useGenevaExporter = false);
    virtual ~OTelRuntime();

    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> GetTracer(const std::string& tracerName);

  protected:
    void Initialize();

    void Shutdown();

    opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider> CreateOtlpTraceProvider(
      const std::string& serviceName);

    opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider> CreateGenevaTraceProvider(const std::string& serviceName);

  private:
    opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider> m_traceProvider;
    std::string m_serviceName = "";
    bool m_useGenevaExporter = false;
  };

} // namespace LkLab
