#include "../common/common.h"

#include <memory>
#include <string>

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"

#include "opentelemetry/sdk/logs/logger_provider.h"

#include "opentelemetry/sdk/trace/tracer_context.h"
#include "opentelemetry/sdk/trace/tracer_context_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"
#include <opentelemetry/sdk/trace/simple_processor.h>
#include "opentelemetry/sdk/trace/simple_processor_factory.h"

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http.h"
#include "opentelemetry/exporters/otlp/otlp_http_client.h"
#include <opentelemetry/exporters/otlp/otlp_http_exporter.h>
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"

#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"

#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/tracer_provider.h"

#include "../IOTelPipeline.h"



namespace MsaLab { namespace Details
{
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

