import { context, trace } from "@opentelemetry/api";
import { S3Client, ListBucketsCommand } from "@aws-sdk/client-s3";
import express from "express";
import http from "http";

const webApp = express();

webApp.get('/', (req, res) => {
    console.log(`sdkv3: handling call at root /.`);
    res.json({
        Message: `Two web methods are provided:  /aws-sdk-call    and    /outgoing-http-call`,
        XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`
    });
});

webApp.get('/aws-sdk-call', (req, res) => {
    console.log(`sdkv3: handling /aws-sdk-call with S3 call.`);
    try {
        const s3Client = new S3Client();
        const command = new ListBucketsCommand({});
        s3Client.send(command)
            .then(function (data) {
                res.json({
                    XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
                    S3Buckets: data.Buckets
                });
            })
            .catch(function (err) {
                console.error(`Error in aws-sdk-call:  ${err.message}`);
                res.status(500).send('Error listing S3 buckets: ' + err.message);
            });
    }
    catch (err) {
        console.error(`error found in S3 call: ${err?.message || err}`);
    }
});

webApp.get('/aws-sdk-call-with-span', async (req, res) => {
    const tracer = trace.getTracer('lambda-tracer');
    await tracer.startActiveSpan('xspan-aws-sdk-call', async (span) => {
        try {
            console.log(`handling /aws-sdk-call-with-span with S3 call.`);
            const s3Client = new S3Client();
            const command = new ListBucketsCommand({});
            const data = await s3Client.send(command);
            res.json({
                XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
                S3Buckets: data.Buckets
            });
        } catch (error) {
            span.recordException(error);
            span.setStatus({ code: trace.SpanStatusCode.ERROR, message: error.message });
            console.error(`error found in S3 call: ${error?.message || error}`);
            res.status(500).send('Error listing S3 buckets: ' + err.message);
            throw error;
        } finally {
            span.end();
        }
    });
});

function fetchHttp(url) {
    return new Promise((resolve, reject) => {
        const req = http.get(url, (res) => {
            let data = "";

            res.on("data", (chunk) => {
                data += chunk;
            });

            res.on("end", () => {
                resolve({ statusCode: res.statusCode, body: data });
            });
        });

        req.on("error", (err) => reject(err));
    });
}

webApp.get("/outgoing-http-call", async (req, res) => {
    try {
        console.log(`handling /outgoing-http-call.`);

        const { statusCode, body } = await fetchHttp("http://aws.amazon.com");

        console.log("Response status code:", statusCode);
        console.log(`Response body: ${body}`);

        res.json({
            XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
            Message: "Pinged aws.amazon.com",
            ResponseBody: body,
        });
    } catch (error) {
        console.error(`Error in outgoing-http-call: ${error.message}`);
        res.status(500).json({ error: `Error in outgoing-http-call:  ${err.message}` });
    }
});

webApp.get('/outgoing-http-call-with-span', async (req, res) => {
    const tracer = trace.getTracer('lambda-tracer');
    await tracer.startActiveSpan('xspan-outgoing-http-call', async (span) => {
        try {
            console.log(`handling /outgoing-http-call-with-span.`);
            const { statusCode, body } = await fetchHttp("http://aws.amazon.com");
            console.log("Response status code:", statusCode);
            console.log(`Response body: ${body}`);
            res.json({
                XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
                Message: "Pinged aws.amazon.com",
                ResponseBody: body,
            });
        } catch (error) {
            span.recordException(error);
            span.setStatus({ code: trace.SpanStatusCode.ERROR, message: error.message });
            console.error(`Error in outgoing-http-call-with-span: ${error.message}`);
            res.status(500).json({ error: `Error in outgoing-http-call-with-span:  ${err.message}` });
            throw error;
        } finally {
            span.end();
        }
    });
});

export default webApp;