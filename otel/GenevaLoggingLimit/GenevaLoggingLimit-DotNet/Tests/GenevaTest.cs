using System.Diagnostics;

namespace GenevaLoggingLimit_DotNet.Tests;

/// <summary>
/// Mirrors the C++ GenevaTest.cpp — entry points that wire up
/// the Geneva/ETW pipeline and run the shared test functions.
/// </summary>
internal static class GenevaTest
{
    private const string ServiceName = "Geneva-Otlp-Test-App";
    private const string TracerName = "MSATraceV1";
    // "DatapointLogLib" is the logger category — the Geneva exporter maps it
    // to the "MSAWarmPathV2" table via TableNameMappings.
    private const string LoggerCategory = "DatapointLogLib";

    public static void TestLogWithGeneva()
    {
        using var pipeline = OTelPipelineFactory.CreateGeneva(ServiceName);
        pipeline.Start();

        using var activitySource = new ActivitySource(TracerName);
        var logger = pipeline.LoggerFactory.CreateLogger(LoggerCategory);

        // TestRunner.TestLog(logger, activitySource);
        TestRunner.TestLogAttributeLimit(logger, activitySource);

        pipeline.Shutdown();
    }

    public static void TestTraceWithGeneva()
    {
        using var pipeline = OTelPipelineFactory.CreateGeneva("OTel-Pipe-With-ETW");
        pipeline.Start();

        using var activitySource = new ActivitySource(TracerName);
        var logger = pipeline.LoggerFactory.CreateLogger(LoggerCategory);

        TestRunner.TestTrace(logger, activitySource);

        pipeline.Shutdown();
    }
}
