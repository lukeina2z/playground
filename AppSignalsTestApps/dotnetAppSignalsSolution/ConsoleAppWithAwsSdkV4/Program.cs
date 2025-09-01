// See https://aka.ms/new-console-template for more information

using System.Threading.Tasks;
using ConsoleApp;

await MyProgram.Main(args);

class MyProgram
{
    public static async Task Foo()
    {
        while (true)
        {
            Bar();
            await Task.Delay(3000); // wait 3 seconds
        }
    }

    static void Bar()
    {
        OTelTraceTest traceTest = new OTelTraceTest();

        var traceId = traceTest.AWSSDKCall();
        System.Console.WriteLine($"AWS Call tracke Id: {traceId}");

        traceId = traceTest.OutgoingHttp();
        System.Console.WriteLine($"Outgoing Http Call tracke Id: {traceId}");

        Console.WriteLine("\n");
    }

    internal static async Task Main(string[] args)
    {
        await Foo();
    }
}


