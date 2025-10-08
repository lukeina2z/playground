using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using ModelContextProtocol.Client;
using Microsoft.Extensions.Logging;
using ModelContextProtocol.Protocol;
using System.Diagnostics;
using System.Net;
using System.Text;

var builder = Host.CreateApplicationBuilder(args);

builder.Configuration 
    .AddEnvironmentVariables()
    .AddUserSecrets<Program>();

var clientTransport = new StdioClientTransport(new()
{
    Name = "Demo Server",
    Command = $"{Path.Combine(AppContext.BaseDirectory, "../../../../", "mcp-adot-server/bin/Debug/net9.0/mcp-adot-server.exe")}",
    Arguments = [],
    EnvironmentVariables = new Dictionary<string, string?>
    {
        { "OTEL_DOTNET_AUTO_TRACES_ADDITIONAL_SOURCES", "Experimental.ModelContextProtocol" },
        {"OTEL_RESOURCE_ATTRIBUTES", "service.name=MCP-Srv-DotNET"},
        { "OTEL_METRICS_EXPORTER", "none"},
        { "OTEL_LOGS_EXPORTER", "otlp"},
        { "OTEL_EXPORTER_OTLP_TRACES_ENDPOINT", "http://localhost:4318/v1/traces"},
        { "OTEL_EXPORTER_OTLP_PROTOCOL", "http/protobuf"},
        { "OTEL_TRACES_SAMPLER", "always_on"},
        {"CORECLR_ENABLE_PROFILING", "1" },
        { "CORECLR_PROFILER", "{918728DD-259F-4A6A-AC2B-B85E1B658318}"},
        { "CORECLR_PROFILER_PATH_64", "c:/ztest/OpenTelemetryDistribution/win-x64/OpenTelemetry.AutoInstrumentation.Native.dll"},
        { "DOTNET_ADDITIONAL_DEPS", "c:/ztest/OpenTelemetryDistribution/AdditionalDeps"},
        { "DOTNET_SHARED_STORE", "c:/ztest/OpenTelemetryDistribution/store"},
        { "DOTNET_STARTUP_HOOKS", "c:/ztest/OpenTelemetryDistribution/net/OpenTelemetry.AutoInstrumentation.StartupHook.dll"},
        { "OTEL_DOTNET_AUTO_HOME", "c:/ztest/OpenTelemetryDistribution"}
    }
});

Console.WriteLine("Setting up stdio transport");

await using var mcpClient = await McpClientFactory.CreateAsync(clientTransport);

Console.WriteLine("Listing tools");

var tools = await mcpClient.ListToolsAsync();

foreach (var tool in tools)
{
    Console.WriteLine($"Connected to server with tools: {tool.Name}");
}

_ = await mcpClient.CallToolAsync(
    "ping_web",
    cancellationToken: CancellationToken.None);


var result = await mcpClient.CallToolAsync(
    "add",
    new Dictionary<string, object?>() { ["a"] = 1, ["b"] = 3  },
    cancellationToken:CancellationToken.None);

Console.WriteLine("Result: " + ((TextContentBlock)result.Content[0]).Text);

System.Threading.Thread.Sleep(5000);

Console.WriteLine("Bye!");

