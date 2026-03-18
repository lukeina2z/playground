using Microsoft.Extensions.Logging;
using OpenTelemetry;
using OpenTelemetry.Exporter.Geneva;
using OpenTelemetry.Logs;
using OpenTelemetry.Resources;
using OpenTelemetry.Trace;

namespace GenevaLoggingLimit_DotNet.Geneva;

/// <summary>
/// Mirrors the C++ OTelPipelineGeneva — sets up OpenTelemetry with the
/// Geneva ETW exporter for both logging and tracing.
/// </summary>
internal class OTelPipelineGeneva : IOTelPipeline
{
    private readonly string _serviceName;
    private TracerProvider? _tracerProvider;
    private ILoggerFactory? _loggerFactory;

    public OTelPipelineGeneva(string serviceName)
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
        _tracerProvider?.Shutdown();
        _tracerProvider?.Dispose();
        _tracerProvider = null;

        _loggerFactory?.Dispose();
        _loggerFactory = null;
    }

    public void Dispose() => Shutdown();

    private void InitLogger()
    {
        // Mirrors the C++ CreateGenevaLoggerProvider with table-name mappings.
        _loggerFactory = Microsoft.Extensions.Logging.LoggerFactory.Create(builder =>
        {
            builder.SetMinimumLevel(LogLevel.Trace);
            builder.AddOpenTelemetry(logging =>
            {
                logging.IncludeScopes = true;
                logging.IncludeFormattedMessage = true;
                logging.AddGenevaLogExporter(options =>
                {
                    options.ConnectionString = "EtwSession=MSADataPointLogger";
                    options.TableNameMappings = new Dictionary<string, string>
                    {
                        ["DatapointLogLib"] = "MSAWarmPathV2",
                        ["libBar"] = "logTableBar"
                    };
                });
            });
        });
    }

    private void InitTracer()
    {
        // Mirrors the C++ CreateGenevaTracerProvider.
        _tracerProvider = Sdk.CreateTracerProviderBuilder()
            .SetResourceBuilder(ResourceBuilder.CreateDefault().AddService(_serviceName))
            .AddSource("*")
            .AddGenevaTraceExporter(options =>
            {
                options.ConnectionString = "EtwSession=OpenTelemetry";
            })
            .Build();
    }
}
