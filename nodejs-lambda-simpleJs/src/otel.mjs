import { callS3, pingWebSite } from "./webapi.mjs"

import { context, trace } from "@opentelemetry/api";

export const myHandler = async (_event, _context) => {

    const tracer = trace.getTracer('lambda-tracer');
    return tracer.startActiveSpan('my-main-span-for-lambda-handler', async (span) => {
        try {
            const responseA = await callS3WithSpan();
            const responseB = await callHttpWithSpan();
            let bodyMsg = "S3 call:\r\n\r\n" + responseA + "\r\n\r\n";
            bodyMsg = bodyMsg + "Ping web site:\r\n\r\n" + responseB;

            const response = {
                statusCode: 200,
                body: bodyMsg
            };
            return response;
        } catch (error) {
            span.recordException(error);
            span.setStatus({ code: trace.SpanStatusCode.ERROR, message: error.message });
            console.error("Error in lambda function", error);
            throw error;
        } finally {
            span.end();
        }
    });
};

async function callS3WithSpan() {
    const tracer = trace.getTracer('lambda-tracer');
    return tracer.startActiveSpan('callS3-With-Span', async (span) => {
        try {
            const response = await callS3();
            // span.setStatus({ code: trace.SpanStatusCode.OK });
            return response;
        } catch (error) {
            span.recordException(error);
            span.setStatus({ code: trace.SpanStatusCode.ERROR, message: error.message });
            throw error;
        } finally {
            span.end();
        }
    });
}

async function callHttpWithSpan() {
    const tracer = trace.getTracer('lambda-tracer');
    return tracer.startActiveSpan('Http-Ping-With-Span', async (span) => {
        try {
            const response = await pingWebSite();
            // span.setStatus({ code: trace.SpanStatusCode.OK });
            return response;
        } catch (error) {
            span.recordException(error);
            span.setStatus({ code: trace.SpanStatusCode.ERROR, message: error.message });
            throw error;
        } finally {
            span.end();
        }
    });
}