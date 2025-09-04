from opentelemetry import trace
from opentelemetry.sdk.trace import TracerProvider
from opentelemetry.sdk.trace.export import BatchSpanProcessor, ConsoleSpanExporter
from opentelemetry.exporter.otlp.proto.grpc.trace_exporter import OTLPSpanExporter

def main():
    # 1. Set up TracerProvider
    trace.set_tracer_provider(TracerProvider())
    tracer = trace.get_tracer(__name__ + "@traceTest.py")

    # 2. OTLP exporter
    otlp_exporter = OTLPSpanExporter(endpoint="http://localhost:4317", insecure=True)
    trace.get_tracer_provider().add_span_processor(BatchSpanProcessor(otlp_exporter))

    # 3. Console exporter (for debugging)
    console_exporter = ConsoleSpanExporter()
    trace.get_tracer_provider().add_span_processor(BatchSpanProcessor(console_exporter))

    # 4. Create sample spans
    with tracer.start_as_current_span("parent-span") as parent:
        print("Parent span started")
        with tracer.start_as_current_span("child-span") as child:
            print("Child span started")
        print("Child span ended")
    print("Parent span ended")

    print("Tracing complete")

print("Starting main")
if __name__ == "__main__":
    main()
    print("Main complete")