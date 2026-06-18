#include "pch.h"
#include "framework.h"
#include "MsaTelemetry.h"

#include "opentelemetry/logs/noop.h"
#include "opentelemetry/trace/noop.h"

namespace
{
    constexpr const char* ServiceName = "Geneva-ETW-Test-App";
    constexpr const char* DefaultTraceScopeName = "MSATraceV1";
    constexpr const char* DefaultLoggerName = "MSALogV1";
    constexpr const char* DataPointLoggerLibraryName = "DatapointLogLib";
    constexpr const char* DataPointTableName = "MSAWarmPathV2";
    constexpr const char* DiagLoggerLibraryName = "DiagLogLib";
    constexpr const char* DiagLogTableName = "MSADiagLogV1";
    constexpr const char* Encoding = "encoding";
    constexpr const char* Version = "1.0.0";
    constexpr const char* EnableTableNameMappings = "enableTableNameMappings";
    constexpr const char* TableNameMappings = "tableNameMappings";
}

namespace MSA { namespace Telemetry {

std::unique_ptr<opentelemetry::exporter::etw::LoggerProvider> CreateGenevaEtwLoggerProvider()
{
    static std::map<std::string, std::string> tableNameMappings = {
        {DataPointLoggerLibraryName, DataPointTableName},
        {DiagLoggerLibraryName, DiagLogTableName}};

    static const std::string MsgPack = "MessagePack";
    static opentelemetry::exporter::etw::TelemetryProviderOptions options = {
        {Encoding, MsgPack},
        {EnableTableNameMappings, true},
        {TableNameMappings, tableNameMappings}};

    return std::make_unique<opentelemetry::exporter::etw::LoggerProvider>(options);
}

std::unique_ptr<opentelemetry::exporter::etw::TracerProvider> CreateGenevaEtwTracerProvider()
{
    return std::make_unique<opentelemetry::exporter::etw::TracerProvider>();
}

GenevaEtwPipeline::GenevaEtwPipeline(const std::string &serviceName) : m_serviceName(serviceName)
{
}

GenevaEtwPipeline::~GenevaEtwPipeline()
{
    Shutdown();
}

void GenevaEtwPipeline::Start()
{
    InitLogger();
    InitTracer();
}

void GenevaEtwPipeline::InitLogger()
{
    m_loggerProvider = CreateGenevaEtwLoggerProvider();
    std::shared_ptr<logs_api::LoggerProvider> api_provider = m_loggerProvider;
    opentelemetry::sdk::logs::Provider::SetLoggerProvider(std::move(api_provider));
}

void GenevaEtwPipeline::InitTracer()
{
    m_tracerProvider = CreateGenevaEtwTracerProvider();

    std::shared_ptr<trace_api::TracerProvider> api_provider = m_tracerProvider;
    opentelemetry::sdk::trace::Provider::SetTracerProvider(std::move(api_provider));

    auto pHttpTraceContext = new opentelemetry::trace::propagation::HttpTraceContext();
    opentelemetry::context::propagation::GlobalTextMapPropagator::SetGlobalPropagator(
        opentelemetry::nostd::shared_ptr<opentelemetry::context::propagation::TextMapPropagator>(
            pHttpTraceContext));
}

void GenevaEtwPipeline::CleanupLogger()
{
    m_loggerProvider.reset();
    std::shared_ptr<logs_api::LoggerProvider> noop = std::make_shared<logs_api::NoopLoggerProvider>();
    logs_sdk::Provider::SetLoggerProvider(std::move(noop));
}

void GenevaEtwPipeline::CleanupTracer()
{
    m_tracerProvider.reset();
    std::shared_ptr<trace_api::TracerProvider> noop = std::make_shared<trace_api::NoopTracerProvider>();
    trace_sdk::Provider::SetTracerProvider(std::move(noop));
}

void GenevaEtwPipeline::Shutdown()
{
    CleanupLogger();
    CleanupTracer();
}


const std::string kOtlpGrpcServer = "http://127.0.0.1:4317";
const std::string kOtlpHttpServer = "http://127.0.0.1:4318";
const std::string kOtlpHttpLogsEndpoint = kOtlpHttpServer + "/v1/logs";
const std::string kOtlpHttpTracesEndpoint = kOtlpHttpServer + "/v1/traces";

namespace
{
    std::string GetProcessExeName()
    {
        wchar_t exePath[MAX_PATH] = {};
        if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) == 0)
            return {};
        const wchar_t* exeName = wcsrchr(exePath, L'\\');
        exeName = exeName ? exeName + 1 : exePath;
        int len = WideCharToMultiByte(CP_UTF8, 0, exeName, -1, nullptr, 0, nullptr, nullptr);
        if (len <= 0) return {};
        std::string result(len - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, exeName, -1, &result[0], len, nullptr, nullptr);
        return result;
    }

    std::string GetProcessCommandLine()
    {
        const wchar_t* cmdLine = GetCommandLineW();
        if (!cmdLine) return {};
        int len = WideCharToMultiByte(CP_UTF8, 0, cmdLine, -1, nullptr, 0, nullptr, nullptr);
        if (len <= 0) return {};
        std::string result(len - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, cmdLine, -1, &result[0], len, nullptr, nullptr);
        return result;
    }
}

std::unique_ptr<logs_sdk::LoggerProvider> CreateOtlpLoggerProvider(const std::string& serviceName)
{
    opentelemetry::exporter::otlp::OtlpHttpLogRecordExporterOptions logger_opts;
    logger_opts.url = kOtlpHttpLogsEndpoint;
    logger_opts.console_debug = false;
    logger_opts.content_type = opentelemetry::exporter::otlp::HttpRequestContentType::kJson;
    logger_opts.timeout = std::chrono::seconds(5);

    std::vector<std::unique_ptr<logs_sdk::LogRecordProcessor>> processors;

    auto otlp_exporter = otlp::OtlpHttpLogRecordExporterFactory::Create(logger_opts);
    logs_sdk::BatchLogRecordProcessorOptions batch_opts;
    processors.push_back(std::unique_ptr<logs_sdk::LogRecordProcessor>(
        new logs_sdk::BatchLogRecordProcessor(std::move(otlp_exporter), batch_opts)));

    // auto ostream_exporter = std::unique_ptr<logs_sdk::LogRecordExporter>(
    //     new logs_exporter::OStreamLogRecordExporter);
    // processors.push_back(
    //     logs_sdk::SimpleLogRecordProcessorFactory::Create(std::move(ostream_exporter)));

    std::string resolvedServiceName = "Geneva-ETW-Test-SVC";

    auto resource_attributes = opentelemetry::sdk::resource::ResourceAttributes{
        {"service.name", resolvedServiceName},
        {"process.pid", static_cast<int64_t>(GetCurrentProcessId())},
        {"process.executable.name", GetProcessExeName()},
        {"process.command_line", GetProcessCommandLine()} };
    auto resource = opentelemetry::sdk::resource::Resource::Create(resource_attributes);

    return logs_sdk::LoggerProviderFactory::Create(std::move(processors), resource);
}

std::unique_ptr<trace_sdk::TracerProvider> CreateOtlpTracerProvider(
    const std::string& serviceName)
{
    opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;
    opts.url = kOtlpHttpTracesEndpoint;
    opts.console_debug = false;
    opts.timeout = std::chrono::seconds(5);

    opts.content_type = opentelemetry::exporter::otlp::HttpRequestContentType::kJson;
    // opts.content_type  = opentelemetry::exporter::otlp::HttpRequestContentType::kBinary;

    // Queue must be large enough to absorb all spans from a busy request
    // before the next scheduled flush. A single login request generates 30+
    // spans; with the previous values (queue=10, batch=3, delay=3s) the queue
    // saturated and silently dropped spans, producing flaky parent/child gaps
    // in Jaeger. Size for ~10 concurrent requests worth of spans.
    opentelemetry::sdk::trace::BatchSpanProcessorOptions batchOption;
    batchOption.max_queue_size = 2048;
    batchOption.schedule_delay_millis = std::chrono::milliseconds(1000);
    batchOption.max_export_batch_size = 256;

    auto otlp_http_exporter = std::make_unique<opentelemetry::exporter::otlp::OtlpHttpExporter>(opts);
    // auto otlp_http_processor = std::make_unique<opentelemetry::sdk::trace::SimpleSpanProcessorFactory>(
    //   std::move(otlp_http_exporter));
    auto otlp_http_processor = std::make_unique<opentelemetry::sdk::trace::BatchSpanProcessor>(
        std::move(otlp_http_exporter), batchOption);

    // auto ostream_exporter = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();
    // auto ostream_processor = std::make_unique<opentelemetry::sdk::trace::BatchSpanProcessor>(
    //   std::move(ostream_exporter), batchOption);
    // auto ostream_processor =
    //     opentelemetry::sdk::trace::SimpleSpanProcessorFactory::Create(std::move(ostream_exporter));

    std::vector<std::unique_ptr<opentelemetry::sdk::trace::SpanProcessor>> processors;
    // processors.push_back(std::move(ostream_processor));
    processors.push_back(std::move(otlp_http_processor));

    std::string resolvedServiceName = "Geneva-OTLP-Test-SVC";
    if (resolvedServiceName.empty())
        resolvedServiceName = serviceName;

    auto resource_attributes =
        opentelemetry::sdk::resource::ResourceAttributes{
            {"service.name", resolvedServiceName},
            {"process.pid", static_cast<int64_t>(GetCurrentProcessId())},
            {"process.executable.name", GetProcessExeName()},
            {"process.command_line", GetProcessCommandLine()} };
    auto resource_ptr = opentelemetry::sdk::resource::Resource::Create(resource_attributes);

    // Default is an always-on sampler.
    std::unique_ptr<opentelemetry::sdk::trace::TracerContext> context =
        opentelemetry::sdk::trace::TracerContextFactory::Create(std::move(processors), resource_ptr);

    auto sdk_provider = opentelemetry::sdk::trace::TracerProviderFactory::Create(std::move(context));

    return sdk_provider;
}






OTelPipelineOtlp::OTelPipelineOtlp(const std::string& serviceName) : m_serviceName(serviceName)
{
}

OTelPipelineOtlp::~OTelPipelineOtlp()
{
    Shutdown();
}

void OTelPipelineOtlp::Start()
{
    InitLogger();
    InitTracer();
}

void OTelPipelineOtlp::InitLogger()
{
    m_loggerProvider = CreateOtlpLoggerProvider(m_serviceName);

    // Set the global Logger provider
    std::shared_ptr<logs_api::LoggerProvider> api_provider = m_loggerProvider;
    opentelemetry::sdk::logs::Provider::SetLoggerProvider(std::move(api_provider));
}

void OTelPipelineOtlp::InitTracer()
{
    m_tracerProvider = CreateOtlpTracerProvider(m_serviceName);

    // Set the global trace provider
    std::shared_ptr<trace_api::TracerProvider> api_provider = m_tracerProvider;
    opentelemetry::sdk::trace::Provider::SetTracerProvider(std::move(api_provider));

    // set global propagator
    auto pHttpTraceContext = new opentelemetry::trace::propagation::HttpTraceContext();
    opentelemetry::context::propagation::GlobalTextMapPropagator::SetGlobalPropagator(
        opentelemetry::nostd::shared_ptr<opentelemetry::context::propagation::TextMapPropagator>(
            pHttpTraceContext));
}

void OTelPipelineOtlp::CleanupLogger()
{
    // Shutdown stops the batch processor from creating new export attempts
    // and drains pending log records. The timeout prevents blocking when the
    // OTLP collector is unreachable (e.g., no local collector on :4318).
    // Without Shutdown(), the destructor chain (~LoggerProvider → ~BatchLogRecordProcessor
    // → ~OtlpHttpClient) blocks indefinitely waiting for in-flight curl sessions.
    if (m_loggerProvider)
    {
        m_loggerProvider->Shutdown(std::chrono::seconds(5));
    }

    // Replace the global provider FIRST so no new callers acquire
    // a provider that is about to be torn down.
    std::shared_ptr<logs_api::LoggerProvider> noop;
    logs_sdk::Provider::SetLoggerProvider(noop);

    m_loggerProvider.reset();
}

void OTelPipelineOtlp::CleanupTracer()
{
    // Shutdown stops the batch processor from creating new export attempts
    // and drains pending spans. The timeout prevents blocking when the
    // OTLP collector is unreachable (e.g., no local collector on :4318).
    // Without Shutdown(), the destructor chain (~TracerProvider → ~BatchSpanProcessor
    // → ~OtlpHttpClient) blocks indefinitely waiting for in-flight curl sessions.
    if (m_tracerProvider)
    {
        m_tracerProvider->Shutdown(std::chrono::seconds(5));
    }

    // Replace the global provider FIRST so no new callers acquire
    // a provider that is about to be torn down.
    std::shared_ptr<opentelemetry::trace::TracerProvider> none;
    trace_sdk::Provider::SetTracerProvider(none);
    std::shared_ptr<trace_api::TracerProvider> noop;
    trace_sdk::Provider::SetTracerProvider(noop);

    m_tracerProvider.reset();
}

void OTelPipelineOtlp::Shutdown()
{
    CleanupLogger();
    CleanupTracer();
}


bool IsOtlpPipelineEnabled()
{
    return false;
}




GenevaPipelineHolder::GenevaPipelineHolder()
{
    m_pipeline = CreateGenevaPipeline(ServiceName);
    m_pipeline->Start();
}

GenevaPipelineHolder::~GenevaPipelineHolder()
{
    if (m_pipeline)
    {
        m_pipeline->Shutdown();
        m_pipeline = nullptr;
    }
}

IGenevaPipeline& GenevaPipelineHolder::GetGenevaPipeline() const
{
    assert(m_pipeline != nullptr);
    return *m_pipeline;
}

std::unique_ptr<IGenevaPipeline> CreateGenevaPipeline(const std::string& name)
{
    if (IsOtlpPipelineEnabled())
    {
        return std::make_unique<OTelPipelineOtlp>(name);
    }

    return std::make_unique<GenevaEtwPipeline>(name);
}

IGenevaPipeline& LazyInitializeGenevaPipeline()
{
    static GenevaPipelineHolder initializer;
    return initializer.GetGenevaPipeline();
}

opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> GetLogger(const std::string& loggerName, const std::string& loggerLibraryName)
{
    auto& pipeline = LazyInitializeGenevaPipeline();
    return pipeline.GetLogger(loggerName, loggerLibraryName, Version);
}

opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> GetLoggerForDataPoint()
{
    return MSA::Telemetry::GetLogger(DefaultLoggerName, DataPointLoggerLibraryName);
}

opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> GetLoggerForDiagnostic()
{
    return MSA::Telemetry::GetLogger(DefaultLoggerName, DiagLoggerLibraryName);
}

opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> GetTracer()
{
    static auto tracer = []() {
        auto& pipeline = LazyInitializeGenevaPipeline();
        return pipeline.GetTracer(DefaultTraceScopeName, Version);
    }();
    return tracer;
}

} // namespace Telemetry
} // namespace MSA
