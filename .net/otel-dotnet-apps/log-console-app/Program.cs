// See https://aka.ms/new-console-template for more information

using Microsoft.Extensions.Logging;
using OpenTelemetry.Logs;

var loggerFactory = LoggerFactory.Create(builder =>
{
    builder.AddConsole();
    builder.AddOpenTelemetry(logging =>
    {
        logging.AddConsoleExporter();
    });
});

var logger = loggerFactory.CreateLogger<Program>();

// ILogger logger = factory.CreateLogger("Program");
logger.LogInformation("Hello World! Logging is {Description}.", "fun");

logger.FoodPriceChanged("artichoke", 9.99);

logger.FoodRecallNotice(
    brandName: "Contoso",
    productDescription: "Salads",
    productType: "Food & Beverages",
    recallReasonDescription: "due to a possible health risk from Listeria monocytogenes",
    companyName: "Contoso Fresh Vegetables, Inc.");

// Dispose logger factory before the application ends.
// This will flush the remaining logs and shutdown the logging pipeline.
loggerFactory.Dispose();

Console.WriteLine("Hello, World!");

internal static partial class LoggerExtensions
{
    [LoggerMessage(LogLevel.Information, "Food `{name}` price changed to `{price}`.")]
    public static partial void FoodPriceChanged(this ILogger logger, string name, double price);

    [LoggerMessage(LogLevel.Critical, "A `{productType}` recall notice was published for `{brandName} {productDescription}` produced by `{companyName}` ({recallReasonDescription}).")]
    public static partial void FoodRecallNotice(
        this ILogger logger,
        string brandName,
        string productDescription,
        string productType,
        string recallReasonDescription,
        string companyName);
}


