
'use strict';

// "@opentelemetry/auto-instrumentations-node"

const oTelApi = require('@opentelemetry/api');
const { BasicTracerProvider, ConsoleSpanExporter, SimpleSpanProcessor } = require('@opentelemetry/sdk-trace-base');
const { CompositePropagator, W3CTraceContextPropagator, W3CBaggagePropagator } = require("@opentelemetry/core");
const { OTLPTraceExporter } = require('@opentelemetry/exporter-trace-otlp-http');
const { AsyncLocalStorageContextManager } = require("@opentelemetry/context-async-hooks");

const { ATTR_SERVICE_NAME } = require('@opentelemetry/semantic-conventions');
const { resourceFromAttributes } = require('@opentelemetry/resources');

function initOTel() {
    oTelApi.diag.setLogger(new oTelApi.DiagConsoleLogger(), oTelApi.DiagLogLevel.ALL);
    oTelApi.diag.debug(`start initializing otel-js.`);

    // Configure span processor to send spans to the exporter
    const exporter = new OTLPTraceExporter({
        url: 'http://localhost:4318/v1/traces',
    });

    // const rsc = await initOTelResource('BAZ-Lambda-Nodejs-Local');
    const rsc = resourceFromAttributes({
        [ATTR_SERVICE_NAME]: 'BAZ-Lambda-Nodejs-Local',
    });

    /**
     * Initialize the OpenTelemetry APIs to use the BasicTracerProvider bindings.
     *
     * This registers the tracer provider with the OpenTelemetry API as the global
     * tracer provider. This means when you call API methods like
     * `opentelemetry.trace.getTracer`, they will use this tracer provider. If you
     * do not register a global tracer provider, instrumentation which calls these
     * methods will receive no-op implementations.
     */
    const oTelTracerProvider = new BasicTracerProvider({
        resource: rsc,
        spanProcessors: [
            new SimpleSpanProcessor(exporter),
            new SimpleSpanProcessor(new ConsoleSpanExporter()),
        ]
    });
    oTelApi.trace.setGlobalTracerProvider(oTelTracerProvider);
    oTelApi.context.setGlobalContextManager(new AsyncLocalStorageContextManager());
    oTelApi.propagation.setGlobalPropagator(new CompositePropagator({
        propagators: [
            new W3CTraceContextPropagator(),
            new W3CBaggagePropagator()]
    }));

    initOTelAutoInst(oTelTracerProvider);
    return oTelTracerProvider;
}

// const { NodeTracerProvider } = require('@opentelemetry/sdk-trace-node');
// const provider = new NodeTracerProvider();
// provider.register();

function initOTelAutoInst(tracerProvider) {
    const { registerInstrumentations } = require('@opentelemetry/instrumentation');
    const { HttpInstrumentation } = require('@opentelemetry/instrumentation-http');
    const { getNodeAutoInstrumentations } = require('@opentelemetry/auto-instrumentations-node');
    const { AwsInstrumentation } = require('@opentelemetry/instrumentation-aws-sdk');

    registerInstrumentations({
        tracerProvider: tracerProvider,
        instrumentations: [
            new AwsInstrumentation({
            }),
            new HttpInstrumentation({
            })]
        // instrumentations: getNodeAutoInstrumentations(),
    });
}

async function initOTelResource(serviceName) {
    // Resource Detector
    const { ATTR_SERVICE_NAME } = require('@opentelemetry/semantic-conventions');
    const { detectResources, resourceFromAttributes, envDetector,
        processDetector,
        hostDetector } = require('@opentelemetry/resources');
    const {
        awsBeanstalkDetector,
        awsEc2Detector,
        awsEcsDetector,
        awsEksDetector,
        awsLambdaDetector
    } = require('@opentelemetry/resource-detector-aws');

    const varFoo = awsBeanstalkDetector.detect();

    const defaultResource = await detectResources({
        detectors: [envDetector, processDetector, hostDetector, awsBeanstalkDetector,
            awsEc2Detector,
            awsEcsDetector,
            awsEksDetector,
            awsLambdaDetector],
    });

    const customResource = resourceFromAttributes({
        [ATTR_SERVICE_NAME]: serviceName,
    });

    return defaultResource.merge(customResource);
}

const tracerProvider = initOTel();
console.log(`Tracer is up now.`);


module.exports = async function jaegerRunner(handler) {
    await handler();

    // flush and close the connection.
    // await tracerProvider.shutdown();
    const provider = oTelApi.trace.getTracerProvider();
    await provider.getDelegate().shutdown();
    console.log(`Tracer is down now.`);
};
