import AWS from "aws-sdk";
import express from "express";
import http from "http";

const webApp = express();

webApp.get('/', (req, res) => {
    console.log(`sdkv2: handling call at root /.`);
    res.send(`Welcome! Two web methods are provided:  /aws-sdk-call    and    /outgoing-http-call`);
});

webApp.get('/aws-sdk-call', async (req, res) => {
    console.log(`sdkv2: handling /aws-sdk-call with S3 call.`);
    try
    {
        const s3 = new AWS.S3();
        const data = await s3.listBuckets().promise();
        res.status(200).json({
            XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
            S3Buckets: data.Buckets
        });
    }
    catch(err)
    {
        console.error(`error found in S3 call: ${err?.message || err}`);
        res.status(500).send('Error listing S3 buckets: ' + err.message);
    }
});

webApp.get('/outgoing-http-call', (req, res) => {
    console.log(`sdkv2: handling /outgoing-http-call.`);
    const httpReq = http.get('http://aws.amazon.com', (httpResponse) => {
        console.log('Response status code:', httpResponse.statusCode);
        let data = "";
        httpResponse.on('data', function (chunk) {
            data += chunk;  // Accumulate the chunks of data
        });

        httpResponse.on('end', function () {
            console.log('Response body:');
            console.log(data); // Complete response body after all chunks
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