using System.Diagnostics.Metrics;
using System.Runtime.InteropServices;
using OpenTelemetry;
using OpenTelemetry.Exporter.Geneva;
using OpenTelemetry.Metrics;

public class Program
{
    private static readonly Meter MyMeter = new("FruitCompany.FruitSales", "1.0");
    private static readonly Counter<long> MyFruitCounter = MyMeter.CreateCounter<long>("FruitsSold");

    public static async Task Main()
    {
        var connectionString = "Account=lukezhangtestaccount;Namespace=HelloGeneva";
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
        {
            connectionString = "Endpoint=unix:/var/etw/mdm_ifx.socket;Account=lukezhangtestaccount;Namespace=HelloGeneva";
        }

        var meterProvider = Sdk.CreateMeterProviderBuilder()
          .AddMeter(MyMeter.Name)
          .AddGenevaMetricExporter(options =>
          {
              options.ConnectionString = connectionString;
          })
          .Build();

        while (true)
        {
            MyFruitCounter.Add(1, new("name", "apple"), new("color", "red"));
            MyFruitCounter.Add(2, new("name", "lemon"), new("color", "yellow"));
            MyFruitCounter.Add(1, new("name", "lemon"), new("color", "yellow"));
            MyFruitCounter.Add(2, new("name", "apple"), new("color", "green"));
            MyFruitCounter.Add(5, new("name", "apple"), new("color", "red"));
            MyFruitCounter.Add(4, new("name", "lemon"), new("color", "yellow"));
            await Task.Delay(1000);
        }

        // Dispose meterProvider at the end of the application.
        meterProvider.Dispose();

        // See https://aka.ms/new-console-template for more information
        Console.WriteLine("Hello, World!");
    }
}


