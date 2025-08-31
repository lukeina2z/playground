using System;
using System.Threading;

namespace ConsoleAppWithNetFx
{
    internal class Program
    {
        private static Timer _timer;

        static void Foo()
        {
            // Create a timer that calls Bar() every 3 seconds (3000 ms)
            _timer = new Timer(_ => Bar(), null, 0, 3000);
        }

        static void Bar()
        {
            AdotTestCalls tests = new AdotTestCalls();
            var traceId = tests.AWSSDKCall();
            System.Console.WriteLine($"AWS Call tracke Id: {traceId}");

            traceId = tests.OutgoingHttp();
            System.Console.WriteLine($"Outgoing Http Call tracke Id: {traceId}");

            Console.WriteLine("The End!");
        }

        static void Main(string[] args)
        {
            Foo();

            Console.WriteLine("Press ENTER to exit...");
            Console.ReadLine();
        }
    }
}

