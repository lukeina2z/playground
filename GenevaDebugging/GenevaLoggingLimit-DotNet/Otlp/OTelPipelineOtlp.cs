using Microsoft.Extensions.Logging;
using OpenTelemetry;
using OpenTelemetry.Exporter;
using OpenTelemetry.Logs;
using OpenTelemetry.Resources;
using OpenTelemetry.Trace;

namespace GenevaLoggingLimit_DotNet.Otlp;

/// <summary>
/// Mirrors the C++ OTelPipelineOtlp — sets up OpenTelemetry with the
/// OTLP HTTP exporter (+ Console exporter) for both logging and tracing.
/// </summary>
internal class OTelPipelineOtlp : IOTelPipeline
{
    private const string OtlpHttpServer = "http://127.0.0.1:4318";
    private const string OtlpHttpLogsEndpoint = OtlpHttpServer + "/v1/logs";
    private const string OtlpHttpTracesEndpoint = OtlpHttpServer + "/v1/traces";

    private readonly string _serviceName;
    private TracerProvider? _tracerProvider;
    private ILoggerFactory? _loggerFactory;

    public OTelPipelineOtlp(string serviceName)
    {
        _serviceName = serviceName;
    }

    public ILoggerFactory LoggerFactory => _loggerFactory
        ?? throw new InvalidOperationException("Pipeline not started");

    public void Start()
    {
        InitLogger();
        InitTracer();
    }

    public void Shutdown()
    {
        _tracerProvider?.ForceFlush();
        _tracerProvider?.Shutdown();
        _tracerProvider?.Dispose();
        _tracerProvider = null;

        _loggerFactory?.Dispose();
        _loggerFactory = null;
    }

    public void Dispose() => Shutdown();

    private void InitLogger()
    {
        // Mirrors the C++ CreateOtlpLoggerProvider:
        //   BatchLogRecordProcessor + OtlpHttpLogRecordExporter
        //   SimpleLogRecordProcessor + OStreamLogRecordExporter
        _loggerFactory = Microsoft.Extensions.Logging.LoggerFactory.Create(builder =>
        {
            builder.SetMinimumLevel(LogLevel.Trace);
            builder.AddOpenTelemetry(logging =>
            {
                logging.IncludeScopes = true;
                logging.IncludeFormattedMessage = true;
                logging.SetResourceBuilder(
                    ResourceBuilder.CreateDefault().AddService(_serviceName));

                // OTLP HTTP exporter (mirrors C++ OtlpHttpLogRecordExporter)
                logging.AddOtlpExporter(options =>
                {
                    options.Endpoint = new Uri(OtlpHttpLogsEndpoint);
                    options.Protocol = OtlpExportProtocol.HttpProtobuf;
                });

                // Console exporter (mirrors C++ OStreamLogRecordExporter)
                logging.AddConsoleExporter();
            });
        });
    }

    private void InitTracer()
    {
        // Mirrors the C++ CreateOtlpTracerProvider:
        //   SimpleSpanProcessor + OStreamSpanExporter
        //   BatchSpanProcessor  + OtlpHttpExporter (max_queue=10, delay=3s, batch=3)
        _tracerProvider = Sdk.CreateTracerProviderBuilder()
            .SetResourceBuilder(ResourceBuilder.CreateDefault().AddService(_serviceName))
            .AddSource("*")
            // Console exporter (mirrors C++ OStreamSpanExporter)
            .AddConsoleExporter()
            // OTLP HTTP exporter (mirrors C++ OtlpHttpExporter with BatchSpanProcessor)
            .AddOtlpExporter(options =>
            {
                options.Endpoint = new Uri(OtlpHttpTracesEndpoint);
                options.Protocol = OtlpExportProtocol.HttpProtobuf;
                options.BatchExportProcessorOptions = new()
                {
                    MaxQueueSize = 10,
                    ScheduledDelayMilliseconds = 3000,
                    MaxExportBatchSize = 3
                };
            })
            .Build();
    }
}
