import { NodeTracerProvider } from '@opentelemetry/sdk-trace-node';
import { AWSXRayPropagator } from '@opentelemetry/propagator-aws-xray';
import { AWSXRayIdGenerator } from '@opentelemetry/id-generator-aws-xray';
import { ConsoleSpanExporter, SimpleSpanProcessor, BatchSpanProcessor } from '@opentelemetry/sdk-trace-base';
import { OTLPTraceExporter } from '@opentelemetry/exporter-trace-otlp-grpc';
import { Resource } from '@opentelemetry/resources';
import { SemanticResourceAttributes } from '@opentelemetry/semantic-conventions';
// import { HttpInstrumentation } from '@opentelemetry/instrumentation-http';
// import { AwsInstrumentation } from '@opentelemetry/instrumentation-aws-sdk';
import { registerInstrumentations } from '@opentelemetry/instrumentation';
import { trace } from '@opentelemetry/api';



// Define the resource (metadata about the Lambda function)
const resource = new Resource({
    [SemanticResourceAttributes.SERVICE_NAME]: 'my-lambda-function',
});

// Create a TracerProvider with AWS X-Ray ID Generator
const tracerProvider = new NodeTracerProvider({
    idGenerator: new AWSXRayIdGenerator(), // Ensures trace ID format matches AWS X-Ray
    resource: resource
});

// Export traces to AWS X-Ray via OTLP
const otlpExporter = new OTLPTraceExporter();

// Log spans to the console (for debugging)
const consoleExporter = new ConsoleSpanExporter();

// Add processors to send traces to multiple destinations
tracerProvider.addSpanProcessor(new SimpleSpanProcessor(consoleExporter)); // Logs spans to console
tracerProvider.addSpanProcessor(new BatchSpanProcessor(otlpExporter)); // Sends spans to AWS X-Ray

// Register the propagator for AWS X-Ray (to ensure trace correlation)
tracerProvider.register({
    propagator: new AWSXRayPropagator(),
});

// Enable automatic instrumentation
// registerInstrumentations({
//     instrumentations: [
//         new HttpInstrumentation(),
//         new AwsInstrumentation({ suppressInternalInstrumentation: true })
//     ]
// });

// Get the tracer instance for manual instrumentation
export const tracer = trace.getTracer('my-lambda-function');

// Ensure the tracer provider is shutdown when the Lambda function exits
export function shutdownTracing() {
    return tracerProvider.shutdown();
}
