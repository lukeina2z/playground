import { S3Client, ListBucketsCommand } from "@aws-sdk/client-s3";
import http from "http";

export async function callS3() {
    console.log(`Make S3 call.`);
    let response = "";
    try {
        const s3Client = new S3Client({ region: "us-west-2" });
        const command = new ListBucketsCommand({});
        const data = await s3Client.send(command);

        response = JSON.stringify({
                XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
                S3Buckets: data.Buckets});
        console.log(`sdkv3: S3 call response: ${response}`);
    }
    catch (err) {
        console.error(`error found in S3 call: ${err?.message || err}`);
    }
    return response;
};

export function pingWebSite() {
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
