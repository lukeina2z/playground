import opentelemetry from "@opentelemetry/api";
import { context, trace } from "@opentelemetry/api";
import { NodeTracerProvider } from "@opentelemetry/sdk-trace-node";
import { ConsoleSpanExporter, SimpleSpanProcessor } from "@opentelemetry/sdk-trace-base";

import { callS3, pingWebSite } from "./src/webapi.mjs"

// Initialize OpenTelemetry Tracer
const provider = new NodeTracerProvider();
provider.addSpanProcessor(new SimpleSpanProcessor(new ConsoleSpanExporter()));
provider.register();

const tracer = opentelemetry.trace.getTracer("my-lambda-fn-01");

function main() {
    const span = tracer.startSpan("my-first-span");
    console.log("Span started: ", span.spanContext());

    // Simulate some work
    setTimeout(() => {
        span.end();
        console.log("Span ended");
    }, 1000);
}

async function fnToCallS3() {
    return new Promise((resolve, reject) => {
        tracer.startActiveSpan('xfnToCallS3', async (span) => {
                try {
                    const result = await callS3();
                    dumpSpan(span);
                    span.end(); // Ensure span is properly ended
                    resolve(result); // Return the result
                } catch (error) {
                    span.recordException(error);
                    span.end();
                    reject(error); // Handle errors properly
                }
        });
    });
}

async function fnToPingWebSite() {
    return new Promise((resolve, reject) => {
        tracer.startActiveSpan('xfnToPingWebSite', async (span) => {
                try {
                    const result = await pingWebSite();
                    dumpSpan(span);
                    span.end(); // Ensure span is properly ended
                    resolve(result);
                } catch (error) {
                    span.recordException(error);
                    span.end();
                    reject(error);
                }
        });
    });
}

export const handler = async (_event, _context) => {
    console.info('Serving lambda request.');

    const eventStr = JSON.stringify(_event, null, 2);
    console.log('Received xxxevent:', eventStr);
    let bodyMsg = "xxxEvent:\r\n\r\n" + eventStr + "\r\n\r\n";

    await new Promise((resolve) => {
        tracer.startActiveSpan('xfnMyLambdaMain', async (parentSpan) => {
            try {
                const responseA = await fnToCallS3();
                const responseB = await fnToPingWebSite();
                bodyMsg += "S3 call:\r\n\r\n" + responseA;
                bodyMsg += "\r\n\r\n" + "Call web site:\r\n\r\n" + responseB;
                dumpSpan(parentSpan);
                parentSpan.end();
            } catch (error) {
                parentSpan.recordException(error);
                parentSpan.end();
                console.error(error);
            } finally {
                resolve(); // Ensure the handler waits for the span to complete
            }
        });
    });

    const response = {
        statusCode: 200,
        body: bodyMsg
    };
    return response;
};

handler();

function dumpSpan(span) {
    console.log(`xxxSpan: name: ${span.name},   traceId: ${span._spanContext.traceId}   spanId: ${span._spanContext.spanId}   parentSpanId: ${span.parentSpanId}`);
}