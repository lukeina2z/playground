using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using ModelContextProtocol.Server;
using System.ComponentModel;

using System.Diagnostics;

//if (!Debugger.IsAttached)
//{
//    Debugger.Launch(); // prompts to attach a debugger
//}

//// OR force a break if already attached
//Debugger.Break();

//HttpClient httpClient = new HttpClient();
//_ = httpClient.GetAsync("http://www.aws.com").Result;

var builder = Host.CreateApplicationBuilder(args);
builder.Logging.AddConsole(consoleLogOptions =>
{
    // Configure all logs to go to stderr
    consoleLogOptions.LogToStandardErrorThreshold = LogLevel.Trace;
});

builder.Services
    .AddMcpServer()
    .WithStdioServerTransport()
    .WithToolsFromAssembly();
await builder.Build().RunAsync();

[McpServerToolType]
public static class CalculatorTool
{
    [McpServerTool, Description("Adds two numbers")]
    public static string Add(int a, int b)
    {

        //HttpClient httpClient = new HttpClient();
        //var ret = httpClient.GetAsync("http://www.amazon.com").Result;
        return $"Sum {a + b}.";
    }

    [McpServerTool, Description("Ping web site with HTTP GET")]
    public static string PingWeb()
    {
        return MakeHtttpCall();
    }

    static string MakeHtttpCall()
    {
        HttpClient httpClient = new HttpClient();
        var ret =  httpClient.GetAsync("http://www.aws.com").Result;
        return ret.ToString();
    }
}