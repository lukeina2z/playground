const { Context, TraceId } = require('@aws-sdk/client-xray');
const { context, trace, ROOT_CONTEXT, SpanKind } = require('@opentelemetry/api');
const { getMyTracer } = require('./mytracer');
const myTest = require("./mytest");

const handler = async (event) => {

    console.log("start lambda B-A-Z with X-Ray and OTel!!!");

    // const xrayContext = getXRayTraceContext();
    // if (!xrayContext) {
    //     return {
    //         statusCode: 500, // You can use 400, 401, etc.
    //         body: JSON.stringify({ 'response': "NoXRayTraceId" }),
    //     };
    // }

    let retVal = "";

    // const { span: bazRootSpan, ctx } = createSpanWithXRayContext();

    const ctx = context.active();
    const tracer = getMyTracer();
    const bazRootSpan = tracer.startSpan('BAZ-Root-Span', {
        // kind: SpanKind.SERVER
    }, ctx);

    await context.with(trace.setSpan(ctx, bazRootSpan), async () => {
        retVal = await await myTest();
    });
    bazRootSpan.end();

    // retVal = await await myTest();
    return {
        statusCode: 200, // You can use 400, 401, etc.
        body: JSON.stringify(retVal),
    };
}

function getXRayTraceContext() {
    const traceHeader = process.env._X_AMZN_TRACE_ID;
    if (!traceHeader) {
        console.log('xyxyxy: No X-Ray trace header found');
        return null;
    } else {
        console.log(`xyxyxy: X-Ray trace header found: ${traceHeader}`);
    }

    const parts = traceHeader.split(';').reduce((acc, part) => {
        const [key, value] = part.split('=');
        acc[key] = value;
        return acc;
    }, {});

    return {
        traceId: parts['Root'],
        parentId: parts['Parent'],
        sampled: parts['Sampled'] === '1'
    };
}

function convertXRayTraceIdToOTel(traceId) {
    // X-Ray traceId: 1-5f84c7a4-3a2e7cf53e9a12a0ec7cfb7e
    // Extract 2nd and 3rd parts
    const parts = traceId.split('-');
    if (parts.length !== 3) return null;

    return parts[1] + parts[2]; // OpenTelemetry needs a 32-char hex
}


function createSpanWithXRayContext() {
    let ctx = context.active();
    const xrayContext = getXRayTraceContext();
    if (xrayContext) {
        const traceId = convertXRayTraceIdToOTel(xrayContext.traceId);
        const spanContext = {
            traceId,
            spanId: xrayContext.parentId,
            traceFlags: xrayContext.sampled ? 1 : 0,
            isRemote: true
        };

        console.log(`xyxyxy: trace id is ${traceId ?? 'N/A'}`);
        console.log(`xyxyxy: parent id is ${xrayContext.parentId ?? 'N/A'}`);

        ctx = trace.setSpanContext(context.active(), spanContext);
    }


    const span = tracer.startSpan('BAZ-Root-lambda-handler', {
        // kind: SpanKind.SERVER
    }, ctx);

    return { span, ctx };
}

module.exports = { handler };
