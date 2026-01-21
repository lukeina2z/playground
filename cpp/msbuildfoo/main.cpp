// msbuildfoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <fmt/core.h>

#include "otelruntime.h"

const char* kGlobalProviderName = "OpenTelemetry-ETW-TLD-Geneva-Example";
std::string providerName = kGlobalProviderName;

using L = std::vector<std::pair<trace_api::SpanContext, std::map<std::string, std::string>>>;

namespace
{
  auto InitTracer()
  {
    static opentelemetry::exporter::etw::TracerProvider tracer_provider;
    auto tracer = tracer_provider.GetTracer(providerName, "1.0");

    return tracer;
  }
  auto InitLogger()
  {
    static opentelemetry::exporter::etw::LoggerProvider logger_provider;
    // auto logger = logger_provider.GetLogger(providerName, "1.0");
    auto logger = logger_provider.GetLogger(std::string(providerName) + "-Logger", "1.0");
    return logger;
  }
}

void TestWithEtwExporter()
{
  const std::string serviceName = "LkLab-Foo-ETW";
  MsaLab::OTelRuntime otel(serviceName, true);

	const std::string tracerName = "InstrScope-Main-ETW";
  auto tracer = otel.GetTracer(tracerName);

  // auto logger = InitLogger();

  auto fooEtw = tracer->StartSpan("main");
  auto scopefooEtw = tracer->WithActiveSpan(fooEtw);

  {
    // Create Span with 1 SpanLink
    auto barEtw = tracer->StartSpan(
      "child", opentelemetry::common::MakeAttributes({ {"key1", "value 1"}, {"key2", 1} }));

    barEtw->SetAttribute("attr_key1", 123);

    auto scopeBar = tracer->WithActiveSpan(barEtw);
    {
      // Create Span with 2 SpanLinks
      auto bazEtw = tracer->StartSpan(
        "grandchild", opentelemetry::common::MakeAttributes({ {"key3", "value 3"}, {"key4", 2} }));

      bazEtw->SetAttribute("attr_key2", 456);
      bazEtw->End();
    }

    barEtw->End();
  }

  fooEtw->End();

  // logger->Info("Hello World ETW!");
}

void TestWithOtlpExporter()
{
  const std::string serviceName = "MsBuild-Foo-OTLP";
  MsaLab::OTelRuntime otel(serviceName);

  const std::string tracerName = "InstrScope-msbuildfoo-Otlp";
  auto tracer = otel.GetTracer(tracerName);

  // auto logger = InitLogger();

  auto s1 = tracer->StartSpan("main");
  auto scopeFoo = tracer->WithActiveSpan(s1);

  {
    L link1 = { {s1->GetContext(), {}} };

    // Create Span with 1 SpanLink
    auto s2 = tracer->StartSpan(
      "child", opentelemetry::common::MakeAttributes({ {"key1", "value 1"}, {"key2", 1} }), link1);

    s2->SetAttribute("attr_key1", 123);

    auto scopeBar = tracer->WithActiveSpan(s2);
    {
      L link2 = { {s1->GetContext(), {}}, {s2->GetContext(), {}} };

      // Create Span with 2 SpanLinks
      auto s3 = tracer->StartSpan(
        "grandchild", opentelemetry::common::MakeAttributes({ {"key3", "value 3"}, {"key4", 2} }),
        link2);

      s3->SetAttribute("attr_key2", 456);

      s3->End();
    }

    s2->End();
  }

  s1->End();

  // logger->Info("Hello World!");
}

int main()
{
  fmt::print("Hello World!\n");

  // TestWithOtlpExporter();

  TestWithEtwExporter();

  std::cout << "Hello, from MSBuild!\n";

  return 0;
}






