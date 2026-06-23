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
        var connectionString = "Account=lukezhangtestv2;Namespace=HelloGenevaV2";
        // var connectionString = "Account=MicrosoftAccountDev;Namespace=lukezhangtest";
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

            meterProvider.ForceFlush(timeoutMilliseconds: 20000);

            await Task.Delay(10000);
        }

        // Dispose meterProvider at the end of the application.
        meterProvider.Dispose();
    }
}