using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleAppWithNetFx
{
    internal class Program
    {
        static void Main(string[] args)
        {
            AdotTestCalls tests = new AdotTestCalls();
            var traceId = tests.AWSSDKCall();
            System.Console.WriteLine($"AWS Call tracke Id: {traceId}");

            traceId = tests.OutgoingHttp();
            System.Console.WriteLine($"Outgoing Http Call tracke Id: {traceId}");

            Console.WriteLine("The End!");
        }
    }
}
