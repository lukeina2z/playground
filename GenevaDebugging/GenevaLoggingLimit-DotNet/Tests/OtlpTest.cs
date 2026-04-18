using System.Diagnostics;

namespace GenevaLoggingLimit_DotNet.Tests;

/// <summary>
/// Mirrors the C++ OtlpTest.cpp — entry points that wire up
/// the OTLP HTTP pipeline and run the shared test functions.
/// </summary>
internal static class OtlpTest
{
    private const string ServiceName = "MsaLab-Foo-Otlp";
    private const string TracerName = "Otlp-Tracer-Foo";
    private const string LoggerName = "Otlp-Logger-Foo";

    public static void TestTraceWithOtlp()
    {
        using var pipeline = OTelPipelineFactory.CreateOtlp(ServiceName);
        pipeline.Start();

        using var activitySource = new ActivitySource(TracerName);
        var logger = pipeline.LoggerFactory.CreateLogger(LoggerName);

        // TestRunner.TestTrace(logger, activitySource);

        pipeline.Shutdown();
    }

    public static void TestLogWithOtlp()
    {
        using var pipeline = OTelPipelineFactory.CreateOtlp(ServiceName);
        pipeline.Start();

        using var activitySource = new ActivitySource(TracerName);
        var logger = pipeline.LoggerFactory.CreateLogger(LoggerName);

        // TestRunner.TestLog(logger, activitySource);
        TestRunner.TestLogAttributeLimit(logger, activitySource);

        pipeline.Shutdown();
    }
}
