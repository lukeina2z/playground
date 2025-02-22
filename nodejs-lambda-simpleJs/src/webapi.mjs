import { S3Client, ListBucketsCommand } from "@aws-sdk/client-s3";
import http from "http";

export function callS3() {
    console.log(`sdkv3: handling /aws-sdk-call with S3 call.`);
    try {
        const s3Client = new S3Client();
        const command = new ListBucketsCommand({});
        s3Client.send(command)
            .then(function (data) {
                const result = JSON.stringify({
                    XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
                    S3Buckets: data.Buckets
                });
                console.log(result);
            })
            .catch(function (err) {
                console.error(`Error in aws-sdk-call:  ${err.message}`);
            });
    }
    catch (err) {
        console.error(`error found in S3 call: ${err?.message || err}`);
    }
};

export function pingWebSite() {
    console.log(`sdkv3: handling /outgoing-http-call.`);
    const httpReq = http.get('http://aws.amazon.com', (httpResponse) => {
        console.log('Response status code:', httpResponse.statusCode);
        let data = "";
        httpResponse.on('data', function (chunk) {
            data += chunk;  // Accumulate the chunks of data
        });

        httpResponse.on('end', function () {
            console.log('Response body:');
            console.log(data); // Complete response body after all chunks
        });
    })

    httpReq.on('error', function (err) {
        console.error(`Error in outgoing-http-call:  ${err.message}`);
    });
};

