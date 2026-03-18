using GenevaLoggingLimit_DotNet.Tests;

namespace GenevaLoggingLimit_DotNet;

internal class Program
{
    static void Main(string[] args)
    {
        // The OTLP exporter enforces SdkLimitOptions.LogRecordAttributeCountLimit,
        // which defaults to 128 (the OTel spec default). With the SDK adding its
        // own attribute ({OriginalFormat}), only 127 user attributes survive.
        // Override via this env var to allow more attributes through.
        Environment.SetEnvironmentVariable("OTEL_LOGRECORD_ATTRIBUTE_COUNT_LIMIT", "512");
        // General fallback (applies to spans/links/events too if their specific
        // env var is not set):
        // Environment.SetEnvironmentVariable("OTEL_ATTRIBUTE_COUNT_LIMIT", "512");

        Console.WriteLine("\n\n Start of Main() \n\n");

        GenevaTest.TestLogWithGeneva();

        // GenevaTest.TestTraceWithGeneva();

        // OtlpTest.TestLogWithOtlp();

        // OtlpTest.TestTraceWithOtlp();

        Console.WriteLine("\n\n End of Main() \n\n");
    }
}
