using System.Diagnostics;
using Microsoft.Extensions.Logging;

namespace GenevaLoggingLimit_DotNet.Tests;

/// <summary>
/// Shared test methods that mirror the C++ test/test.cpp functions.
/// Both Geneva and OTLP tests call into these.
/// </summary>
internal static class TestRunner
{
    /// <summary>
    /// Mirrors the C++ TestLog function.
    /// Creates a span, logs at various severity levels (with and without EventId
    /// and trace context), then logs once more after the span has ended.
    /// </summary>
    public static void TestLog(ILogger logger, ActivitySource activitySource)
    {
        using (var activity = activitySource.StartActivity("Test-Log-Main-Span", ActivityKind.Server))
        {
            // Activity.Current is now set — trace context is automatically
            // captured by the OpenTelemetry logger provider.

            logger.LogCritical("Hello <Fatal> Otlp!");       // C++ Fatal → .NET Critical
            logger.LogError("Hello <Error> Otlp!");

            var eventId = new EventId(0x12345678, "Company.Component.SubComponent.FunctionName");
            logger.LogInformation(eventId, "Info message from {pid}", 12347);
            logger.LogError(eventId, "Error message from {pid}", 12347);

            logger.LogInformation("Hello <Info> Otlp!");
            logger.LogDebug("Hello <Debug> Otlp!");

            // In .NET the trace/span IDs are attached automatically via Activity.Current.
            logger.LogDebug("xyz-body");

            activity?.Stop();
        }

        // After the span scope — no trace context expected.
        logger.LogDebug("xyzxyz - The end. No trace context expected.");
    }

    /// <summary>
    /// Mirrors the C++ TestLogAttributeLimit function.
    /// Creates 300 key-value attributes and logs them in a single record to
    /// test the ETW 128-EVENT_DATA_DESCRIPTOR limit.
    /// </summary>
    public static void TestLogAttributeLimit(ILogger logger, ActivitySource activitySource)
    {
        const int testAttributeCount = 300;

        // Build 300 short key/value pairs (K0=V0 … K299=V299) — mirrors BuildTestData() in C++.
        var attributes = new Dictionary<string, object?>(testAttributeCount);
        for (int i = 0; i < testAttributeCount; i++)
        {
            attributes[$"K{i}"] = $"V{i}";
        }

        // BeginScope attaches the attributes to the log record (with IncludeScopes = true).
        using (logger.BeginScope(attributes))
        {
            logger.LogInformation("GenevaLogAttributeLimitTest-DotNet");
        }
    }

    /// <summary>
    /// Mirrors the C++ TestTrace function.
    /// Creates a parent → child → grandchild span hierarchy with SpanLinks,
    /// attributes, and events.
    /// </summary>
    public static void TestTrace(ILogger logger, ActivitySource activitySource)
    {
        logger.LogInformation("Inside TestTrace, Before span creation.");

        using var s1 = activitySource.StartActivity("Test-Trace-Main-Span", ActivityKind.Server);
        if (s1 == null) return;

        // Child span with 1 link (to s1)
        var link1 = new[] { new ActivityLink(s1.Context) };
        using var s2 = activitySource.StartActivity(
            "Child-Span",
            ActivityKind.Client,
            parentContext: default(ActivityContext),
            tags: new KeyValuePair<string, object?>[]
            {
                new("key1", "value 1"),
                new("key2", 1)
            },
            links: link1);

        s2?.SetTag("attr_key1", 123);

        // Grandchild span with 2 links (to s1 and s2)
        var links2 = new[]
        {
            new ActivityLink(s1.Context),
            new ActivityLink(s2?.Context ?? default)
        };
        using var s3 = activitySource.StartActivity(
            "Grandchild-Span",
            ActivityKind.Server,
            parentContext: default(ActivityContext),
            tags: new KeyValuePair<string, object?>[]
            {
                new("key3", "value 3"),
                new("key4", 2)
            },
            links: links2);

        s3?.SetTag("attr_key2", 456);

        logger.LogInformation("Inside Child-Span Scope : Test Log API!");

        s3?.Stop();

        // Add event on the child span (after grandchild ended) — mirrors C++ s2->AddEvent(...)
        s2?.AddEvent(new ActivityEvent("An event in Child-Span",
            tags: new ActivityTagsCollection(new KeyValuePair<string, object?>[]
            {
                new("event_attr1", "event value 1")
            })));

        s2?.Stop();
        s1.Stop();
    }
}
