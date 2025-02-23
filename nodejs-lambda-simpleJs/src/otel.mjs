import { callS3, pingWebSite } from "./webapi.mjs"

import { context, trace } from "@opentelemetry/api";

export const myHandler = async (_event, _context) => {

    const tracer = trace.getTracer('lambda-tracer');
    return tracer.startActiveSpan('my-main-span-for-lambda-handler', async (span) => {
        try {
            console.log("Lambda function started");
            const responseA = await callS3();
            const responseB = await pingWebSite();
            let bodyMsg = "S3 call:\r\n\r\n" + responseA + "\r\n\r\n";
            bodyMsg = bodyMsg + "Ping web site:\r\n\r\n" + responseB;

            const response = {
                statusCode: 200,
                body: bodyMsg
            };
            
            console.log("Lambda function completed");
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
