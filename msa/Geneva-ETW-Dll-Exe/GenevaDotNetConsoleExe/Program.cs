using System.Diagnostics.Metrics;
using System.Runtime.InteropServices;
using OpenTelemetry;
using OpenTelemetry.Exporter.Geneva;
using OpenTelemetry.Metrics;

public class Program
{
    private static readonly Meter MyMeter = new("FruitCompany.FruitSales", "1.0");
    private static readonly Counter<long> MyFruitCounter = MyMeter.CreateCounter<long>("FruitsSold");
    private static readonly Random Rng = new();

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

        // Tracks elapsed iterations so we can simulate a demand curve over time.
        var tick = 0;

        while (true)
        {
            MyFruitCounter.Add(NextSale(1, tick), new("name", "apple"), new("color", "red"));
            MyFruitCounter.Add(NextSale(2, tick), new("name", "lemon"), new("color", "yellow"));
            MyFruitCounter.Add(NextSale(1, tick), new("name", "lemon"), new("color", "yellow"));
            MyFruitCounter.Add(NextSale(2, tick), new("name", "apple"), new("color", "green"));
            MyFruitCounter.Add(NextSale(5, tick), new("name", "apple"), new("color", "red"));
            MyFruitCounter.Add(NextSale(4, tick), new("name", "lemon"), new("color", "yellow"));

            // meterProvider.ForceFlush(timeoutMilliseconds: 20000);

            tick++;

            // Wait a random interval between 1 and 10 seconds so the data
            // points arrive at irregular times, like real-world sales.
            var delayMs = Rng.Next(1000, 10001);
            await Task.Delay(delayMs);
        }

        // Dispose meterProvider at the end of the application.
        // meterProvider.Dispose();
    }

    // Produces a realistic-looking sales figure by combining a smooth demand
    // curve (sine wave) with random jitter and occasional spikes, so the
    // dashboard chart shows natural ups and downs instead of a flat line.
    private static long NextSale(int baseAmount, int tick)
    {
        // Smooth demand curve oscillating around the base amount, simulating
        // periods of higher and lower demand over time.
        var demandCurve = baseAmount * (1.0 + 0.5 * Math.Sin(tick / 6.0));

        // Random jitter of roughly +/- 40% to mimic natural variation.
        var jitter = demandCurve * (Rng.NextDouble() * 0.8 - 0.4);

        // Occasional spike to simulate a promotion or sudden rush of buyers.
        var spike = Rng.NextDouble() < 0.1 ? baseAmount * Rng.Next(2, 5) : 0;

        // Counters only accept non-negative deltas, so clamp to at least 1.
        var ret = Math.Max(1, (long)Math.Round(demandCurve + jitter + spike));
        return ret;
    }
}