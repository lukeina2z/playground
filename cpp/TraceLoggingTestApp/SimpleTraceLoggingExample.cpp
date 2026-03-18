#include "SimpleTraceLoggingExample.h"

// Define a handle to a TraceLogging provider
TRACELOGGING_DEFINE_PROVIDER(
    g_hMyComponentProvider,
    "SimpleTraceLoggingProvider",
    // {0205c616-cf97-5c11-9756-56a2cee02ca7}
    (0x0205c616, 0xcf97, 0x5c11, 0x97, 0x56, 0x56, 0xa2, 0xce, 0xe0, 0x2c, 0xa7));

void main()
{

    char sampleValue[] = "Sample value";

    // Register the provider
    TraceLoggingRegister(g_hMyComponentProvider);

    // Log an event
    TraceLoggingWrite(g_hMyComponentProvider, // handle to my provider
        "HelloWorldTestEvent",              // Event Name that should uniquely identify your event.
        TraceLoggingValue(sampleValue, "TestMessage")); // Field for your event in the form of (value, field name).

    // Stop TraceLogging and unregister the provider
    TraceLoggingUnregister(g_hMyComponentProvider);
}


