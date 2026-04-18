using Microsoft.Extensions.Logging;

namespace GenevaLoggingLimit_DotNet;

/// <summary>
/// Mirrors the C++ IOTelPipeline interface.
/// </summary>
public interface IOTelPipeline : IDisposable
{
    void Start();
    void Shutdown();

    /// <summary>
    /// The logger factory created by this pipeline.
    /// Use <c>LoggerFactory.CreateLogger(categoryName)</c> to obtain an ILogger.
    /// </summary>
    ILoggerFactory LoggerFactory { get; }
}

public static class OTelPipelineFactory
{
    public static IOTelPipeline CreateGeneva(string serviceName)
        => new Geneva.OTelPipelineGeneva(serviceName);

    public static IOTelPipeline CreateOtlp(string serviceName)
        => new Otlp.OTelPipelineOtlp(serviceName);
}
