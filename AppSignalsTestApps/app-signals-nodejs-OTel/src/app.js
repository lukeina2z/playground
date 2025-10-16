'use strict';

const { context, trace, ROOT_CONTEXT } = require('@opentelemetry/api');
const awsCalls = require('./awsS3Test');


const http = require('http');



function pingWebSite() {
    console.log(`Ping web site.`);

    return new Promise((resolve, reject) => {
        const httpReq = http.get('http://aws.amazon.com', (httpResponse) => {
            console.log('Response status code:', httpResponse.statusCode);
            let data = `XRayTraceID: ${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}\r\n`;
            httpResponse.on('data', (chunk) => {
                data += chunk;  // Accumulate the chunks of data
            });

            httpResponse.on('end', () => {
                console.log(`Response body: ${data}`);
                resolve(data);
            });
        });

        httpReq.on('error', (error) => {
            console.error(`Error in outgoing-http-call:  ${err.message}`);
            reject(error);
        });
    });
};


async function doWork(parent, tracer) {
    // Start another span. In this example, the main method already started a
    // span, so that'll be the parent span, and this will be a child span.
    const ctx = trace.setSpan(context.active(), parent);
    const span = tracer.startSpan('xy-do-Work', undefined, ctx);

    // simulate some random work.
    for (let i = 0; i <= Math.floor(Math.random() * 40000000); i += 1) {
        // empty
    }

    // Set attributes to the span.
    span.setAttribute('color', 'green');

    // Annotate our span to capture metadata about our operation
    span.addEvent('invoking doWork');
    const newContext = trace.setSpan(context.active(), span);
    await context.with(newContext, async () => {
        await pingWebSite();
        await awsCalls.s3Call();
    });
    span.end();
}

module.exports = async function main() {
    const tracer = trace.getTracer('example-basic-tracer-node');
    // Create a span. A span must be closed.
    const parentSpan = tracer.startSpan('xy-top-root-span');
    for (let i = 0; i < 1; i += 1) {
        await doWork(parentSpan, tracer);
    }
    // Be sure to end the span.
    parentSpan.end();
}

