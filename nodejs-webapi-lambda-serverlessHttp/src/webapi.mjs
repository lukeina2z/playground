import { S3Client, ListBucketsCommand } from "@aws-sdk/client-s3";
import express from "express";
import http from "http";

const webApp = express();

webApp.get('/', (req, res) => {
    console.log(`sdkv3: handling call at root /.`);
    res.send(`Welcome! Two web methods are provided:  /aws-sdk-call    and    /outgoing-http-call`);
});

webApp.get('/aws-sdk-call', (req, res) => {
    console.log(`sdkv3: handling /aws-sdk-call with S3 call.`);
    try
    {
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
    catch(err)
    {
        console.error(`error found in S3 call: ${err?.message || err}`);
    }
});

webApp.get('/outgoing-http-call', (req, res) => {
    console.log(`sdkv3: handling /outgoing-http-call.`);
    const httpReq = http.get('http://aws.amazon.com', (httpResponse) => {
        console.log('Response status code:', httpResponse.statusCode);
        let data = "";
        httpResponse.on('data', function (chunk) {
            data += chunk;  // Accumulate the chunks of data
        });

        httpResponse.on('end', function () {
            console.log(`Response body: ${data}`);
            res.json({
                XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
                Message: "Pinged aws.amazon.com",
                ResponseBody: data
            });
        });
    })

    httpReq.on('error', function (err) {
        console.error(`Error in outgoing-http-call:  ${err.message}`);
    });
});

export default webApp;