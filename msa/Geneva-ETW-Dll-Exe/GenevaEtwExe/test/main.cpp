// msbuildfoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

#include "../../GenevaEtwDll/MsaTelemetry.h"

extern void TestOTelMetrics();


void TestLogWithGenevaEtwExporter()
{
    auto logger = MSA::Telemetry::GetLoggerForDataPoint();
    logger->Fatal("Hello <Fatal> Otlp!");
    logger->Error("Hello <Error> Otlp!");
    logger->Info("Hello <Info> Otlp!");
    logger->Debug("xyzxyz - The end. No trace context expected.");
}

void TestTraceWithGenevaEtwExporter()
{
    static auto tracer = MSA::Telemetry::GetTracer();
    trace_api::StartSpanOptions optionsS2;
    optionsS2.kind = trace_api::SpanKind::kClient;

    // Create Span with 1 SpanLink
    auto s2 = tracer->StartSpan("xyxyxy-Span", opentelemetry::common::MakeAttributes({ {"key1", "value 1"}, {"key2", 1} }), optionsS2);

    s2->SetAttribute("attr_key1", 123);

    s2->End();
}

int main()
{
    TestOTelMetrics();

    TestLogWithGenevaEtwExporter();

    TestTraceWithGenevaEtwExporter();
  
    std::cout << "\n\n End of Main() \n\n";
    return 0;
}
