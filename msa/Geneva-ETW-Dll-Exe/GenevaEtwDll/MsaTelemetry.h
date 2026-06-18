#pragma once

#define HAVE_MSGPACK

#include "GenevaEtwDll.h"

#include <deque>
#include <string>

#include "opentelemetry/common/attribute_value.h"
#include "opentelemetry/common/key_value_iterable_view.h"
#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"
#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"
#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/logs/logger.h"

#include "opentelemetry/logs/provider.h"

#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/nostd/shared_ptr.h"
#include "opentelemetry/sdk/logs/batch_log_record_processor.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/resource/resource.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/sdk/trace/simple_processor.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_context.h"
#include "opentelemetry/sdk/trace/tracer_context_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/trace/span_context.h"
#include "opentelemetry/trace/tracer.h"
#include "opentelemetry/trace/tracer_provider.h"





#include "opentelemetry/trace/trace_id.h"
#include "opentelemetry/trace/span_id.h"
#include "opentelemetry/trace/trace_flags.h"




#include "opentelemetry/logs/noop.h"
#include "opentelemetry/trace/noop.h"

#include <cassert>
#include <map>
#include <string>
#include <vector>

#include "opentelemetry/common/attribute_value.h"
#include "opentelemetry/common/key_value_iterable_view.h"
#include "opentelemetry/nostd/shared_ptr.h"

#include "opentelemetry/logs/logger.h"
#include "opentelemetry/logs/logger_provider.h"

#include "opentelemetry/trace/tracer.h"
#include "opentelemetry/trace/tracer_provider.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/trace/span_context.h"

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"
#include "opentelemetry/exporters/geneva/geneva_logger_exporter.h"
#include "opentelemetry/exporters/geneva/geneva_tracer_exporter.h"
#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"

#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"

#include <opentelemetry/sdk/trace/simple_processor.h>
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_context.h"
#include "opentelemetry/sdk/trace/tracer_context_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/trace/tracer_provider.h"

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"
#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"

#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"
#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/exporters/otlp/otlp_http_log_record_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_log_record_exporter_options.h"
#include "opentelemetry/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/batch_log_record_processor.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/resource/resource.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_context.h"
#include "opentelemetry/sdk/trace/tracer_context_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/trace/tracer_provider.h"

namespace MSA { namespace Telemetry {

namespace logs_api = opentelemetry::logs;
namespace logs_sdk = opentelemetry::sdk::logs;
namespace logs_exporter = opentelemetry::exporter::logs;

namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;

namespace otlp = opentelemetry::exporter::otlp;

struct IGenevaPipeline
{
public:
    IGenevaPipeline() = default;
    virtual ~IGenevaPipeline() = default;

    virtual void Start() = 0;
    virtual void Shutdown() = 0;

    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> GetTracer(const std::string& name,
        const std::string& version = "")
    {
        auto provider = opentelemetry::trace::Provider::GetTracerProvider();
        return provider->GetTracer(name, version);
    }

    opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> GetLogger(const std::string& name,
        const std::string& libName = "",
        const std::string& version = "")
    {
        auto provider = opentelemetry::logs::Provider::GetLoggerProvider();
        return provider->GetLogger(name, libName, version);
    }
};

std::unique_ptr<IGenevaPipeline> CreateGenevaPipeline(const std::string& name);

class GenevaEtwPipeline : public IGenevaPipeline
{
public:
    GenevaEtwPipeline(const std::string& serviceName);
    virtual ~GenevaEtwPipeline();

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


class OTelPipelineOtlp : public IGenevaPipeline
{
public:
    OTelPipelineOtlp(const std::string& serviceName);
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


class GenevaPipelineHolder
{
public:
    GenevaPipelineHolder();
    ~GenevaPipelineHolder();

    IGenevaPipeline& GetGenevaPipeline() const;

private:
    std::unique_ptr<IGenevaPipeline> m_pipeline;
};

GENEVAETWDLL_API opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> GetLoggerForDataPoint();

GENEVAETWDLL_API opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> GetLoggerForDiagnostic();

GENEVAETWDLL_API opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> GetTracer();

} // namespace Telemetry
} // namespace MSA
