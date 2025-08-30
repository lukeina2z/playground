// See https://aka.ms/new-console-template for more information

using ConsoleApp;

OTelTraceTest traceTest = new OTelTraceTest();

var traceId = traceTest.AWSSDKCall();
System.Console.WriteLine($"AWS Call tracke Id: {traceId}");

traceId = traceTest.OutgoingHttp();
System.Console.WriteLine($"Outgoing Http Call tracke Id: {traceId}");

Console.WriteLine("Hello, World!");
