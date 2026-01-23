#include "common.h"

#include <memory>
#include <string>

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"

#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"

#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/common/global_log_handler.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"


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

#include "../geneva/otelgeneva.h"
#include "../otlp/otelotlp.h"

  //namespace logs_api = opentelemetry::logs;
  //namespace logs_sdk = opentelemetry::sdk::logs;
  // namespace logs_exporter = opentelemetry::exporter::logs;

  namespace trace_api = opentelemetry::trace;
  namespace trace_sdk = opentelemetry::sdk::trace;
  namespace trace_exporter = opentelemetry::exporter::trace;


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