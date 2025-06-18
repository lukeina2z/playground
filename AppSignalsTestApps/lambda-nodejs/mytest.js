'use strict';

const { context, trace, ROOT_CONTEXT, SpanKind } = require('@opentelemetry/api');
const { getMyTracer } = require("./mytracer");
const { doWorkS3Call } = require("./s3");
const { doWorkHttpCall } = require("./http");

async function doWork(tracer) {
    const ctx = context.active();
    const spanDoWork = tracer.startSpan('BAZ-do-Work', {
        // kind: SpanKind.SERVER
    }, ctx);

    // Set attributes to the span.
    spanDoWork.setAttribute('color', 'green');

    // Annotate our span to capture metadata about our operation
    spanDoWork.addEvent('invoking doWork');
    const newContext = trace.setSpan(context.active(), spanDoWork);
    let retValS3Call = "";
    await context.with(newContext, async () => {
        retValS3Call = await doWorkS3Call(tracer);
    });

    let retValHttpCall = "";
    await context.with(newContext, async () => {
        retValHttpCall = await doWorkHttpCall(tracer);
    });

    spanDoWork.end();
    return { "s3": retValS3Call, "http": retValHttpCall };
}


module.exports = async function main() {
    const ctx = context.active();
    const tracer = getMyTracer();
    const bazMainSpan = tracer.startSpan('BAZ-Main-span', {
        // kind: SpanKind.SERVER
    }, ctx);

    let retVal = "";
    await context.with(trace.setSpan(ctx, bazMainSpan), async () => {
        retVal = await doWork(tracer);
    });

    bazMainSpan.end();
    return retVal;
}
