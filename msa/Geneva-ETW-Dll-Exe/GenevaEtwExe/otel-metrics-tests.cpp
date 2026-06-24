



#include "opentelemetry/exporters/geneva/metrics/exporter.h"
#include "opentelemetry/metrics/provider.h"
#include "opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"

#include <chrono>
#include <thread>

namespace geneva_exporter = opentelemetry::exporter::geneva::metrics;
namespace metrics_api = opentelemetry::metrics;
namespace metrics_sdk = opentelemetry::sdk::metrics;
namespace nostd = opentelemetry::nostd;


nostd::shared_ptr<metrics_api::MeterProvider> GetMsaMeterProvider(const std::string& metric_account, const std::string& metric_namespace)
{
	// Create a new Geneva Metrics Exporter with your MetricAccount and MetricNamespace:

#if defined(_WIN32)
	std::string connection_string = "Account=" + metric_account + ";Namespace=" + metric_namespace;
#else
	// replace "@/genevametrics/ifx.socket" in below connection_string with the actual Unix Domain socket path the agent is listening on.
	std::string connection_string = "Endpoint=unix://@/genevametrics/ifx.socket;Account=" + metric_account + ";Namespace=" + metric_namespace;
#endif

	geneva_exporter::ExporterOptions options{ connection_string };
	std::unique_ptr<metrics_sdk::PushMetricExporter> exporter{ new geneva_exporter::Exporter(options) };


	// Create a PeriodicExportingMetricReader with the Geneva Metrics Exporter :

	metrics_sdk::PeriodicExportingMetricReaderOptions reader_options;
	std::unique_ptr<metrics_sdk::MetricReader> reader{
	  new metrics_sdk::PeriodicExportingMetricReader(std::move(exporter),
		reader_options) };

	// Create a MeterProvider and attach the PeriodicExportingMetricReader to it :

	auto api_provider = std::shared_ptr<metrics_api::MeterProvider>(
		new metrics_sdk::MeterProvider());

	auto sdk_provider = std::static_pointer_cast<metrics_sdk::MeterProvider>(api_provider);
	sdk_provider->AddMetricReader(std::move(reader));

	// Set the MeterProvider as the default provider:
	// metrics_api::Provider::SetMeterProvider(api_provider);

	return api_provider;
}

void InitOTelMetrics(const std::string& metric_account, const std::string& metric_namespace)
{
	auto api_provider = GetMsaMeterProvider(metric_account, metric_namespace);

	// Set the MeterProvider as the default provider:
	metrics_api::Provider::SetMeterProvider(api_provider);

}

constexpr int kLoopCount = 300;
constexpr int kSleepSeconds = 1;
const char* kMetricAccount = "lukezhangtestv2";
const char* kMetricNamespaceOne = "OTelCppMetricsTestsOne";
const char* kMetricNamespaceTwo = "OTelCppMetricsTestsTwo";

void TestOTelMetricsWithDefaultProvider()
{
	auto provider = metrics_api::Provider::GetMeterProvider();
	auto meter = provider->GetMeter("my_meter_name", "1.2.0");
	int count = kLoopCount;
	while (count > 0)
	{
		// Create a Counter instrument and report measurements :

		auto http_request_completed = meter->CreateUInt64Counter("http_request_completed");

		http_request_completed->Add(40, { {"request.type", "GET"} });
		http_request_completed->Add(20, { {"request.type", "PUT"} });
		http_request_completed->Add(2, { {"request.type", "GET"} });
		http_request_completed->Add(50, { {"request.type", "PUT"} });

		// Create a Histogram instrument and report measurements :

		auto http_response_size = meter->CreateUInt64Histogram("http_response_size");

		http_response_size->Record(1000 /* response size */, { {"request.type", "PUT"} }, opentelemetry::context::Context{});

		// Sleep for 3 seconds before the next loop iteration.
		std::this_thread::sleep_for(std::chrono::seconds(kSleepSeconds));
		count--;
	}
}

void TestOTelMetricsOne()
{
	auto provider = GetMsaMeterProvider(kMetricAccount, kMetricNamespaceOne);
	auto meter = provider->GetMeter("my_meter_name_one", "1.2.0");
	int count = kLoopCount / 2;
	while (count > 0)
	{
		// Create a Counter instrument and report measurements :

		auto http_request_completed = meter->CreateUInt64Counter("http_request_completed_One");

		http_request_completed->Add(40, { {"request.type", "GET"} });
		http_request_completed->Add(20, { {"request.type", "PUT"} });
		http_request_completed->Add(2, { {"request.type", "GET"} });
		http_request_completed->Add(50, { {"request.type", "PUT"} });

		// Create a Histogram instrument and report measurements :

		auto http_response_size = meter->CreateUInt64Histogram("http_response_size_One");

		http_response_size->Record(1000 /* response size */, { {"request.type", "PUT"} }, opentelemetry::context::Context{});

		// Sleep for 3 seconds before the next loop iteration.
		std::this_thread::sleep_for(std::chrono::seconds(kSleepSeconds));
		count--;
	}
}

void TestOTelMetricsTwo()
{
	auto provider = GetMsaMeterProvider(kMetricAccount, kMetricNamespaceTwo);
	auto meter = provider->GetMeter("my_meter_name_two", "1.2.0");
	int count = kLoopCount;
	while (count > 0)
	{
		// Create a Counter instrument and report measurements :

		auto http_request_completed = meter->CreateUInt64Counter("http_request_completed_Two");

		http_request_completed->Add(40, { {"request.type", "GET"} });
		http_request_completed->Add(20, { {"request.type", "PUT"} });
		http_request_completed->Add(2, { {"request.type", "GET"} });
		http_request_completed->Add(50, { {"request.type", "PUT"} });

		// Create a Histogram instrument and report measurements :

		auto http_response_size = meter->CreateUInt64Histogram("http_response_size_Two");

		http_response_size->Record(1000 /* response size */, { {"request.type", "PUT"} }, opentelemetry::context::Context{});

		// Sleep for 3 seconds before the next loop iteration.
		std::this_thread::sleep_for(std::chrono::seconds(kSleepSeconds));
		count--;
	}
}


void TestOTelMetrics()
{
	InitOTelMetrics(kMetricAccount, "OTelCppMetricsTests");

	// Run the two metric tests concurrently on separate threads.
	std::thread thread_one(TestOTelMetricsOne);
	std::thread thread_two(TestOTelMetricsTwo);

	TestOTelMetricsWithDefaultProvider();

	// Wait for both threads to finish before returning.
	thread_one.join();
	thread_two.join();
}