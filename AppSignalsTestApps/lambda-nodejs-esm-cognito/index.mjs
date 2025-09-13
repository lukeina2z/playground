// const { S3Client, ListBucketsCommand } = require("@aws-sdk/client-s3");
// const http = require("http");

import { S3Client, ListBucketsCommand } from "@aws-sdk/client-s3";
import http from "http";

import { CognitoIdentityProviderClient, ListUserPoolsCommand } from "@aws-sdk/client-cognito-identity-provider";


async function callAwsCognito() {
    console.log(`Make AWS Cognito call.`);

    const client = new CognitoIdentityProviderClient({ region: "us-west-2" }); // change region if needed
    let result = "";
    try {
        const command = new ListUserPoolsCommand({ MaxResults: 5 });
        result = await client.send(command);
        console.log("User Pools:", result.UserPools);
    } catch (err) {
        console.error("Error listing user pools:", err);
    }

    return result;
};


async function callS3() {
    console.log(`Make S3 call.`);
    let response = "";
    try {
        const s3Client = new S3Client({ region: "us-west-2" });
        const command = new ListBucketsCommand({});
        const data = await s3Client.send(command);

        response = JSON.stringify({
            XRayTraceID: `${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`,
            S3Buckets: data.Buckets
        });
        console.log(`sdkv3: S3 call response: ${response}`);
    }
    catch (err) {
        console.error(`error found in S3 call: ${err?.message || err}`);
    }
    return response;
};

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

const myHandler = async (_event, _context) => {
    await callAwsCognito();
    const rspS3 = await callS3();
    const rspHttp = await pingWebSite();
    const response = {
        statusCode: 200,
        body: ""
    };
    return response;
};


import middy from "@middy/core";
import httpHeaderNormalizer from "@middy/http-header-normalizer";
import httpJsonBodyParser from "@middy/http-json-body-parser";
// import validator from "@middy/validator";
// import { injectLambdaContext } from "@aws-lambda-powertools/logger";
// import { Logger } from "@aws-lambda-powertools/logger";

const handler = middy(myHandler)
  // .use(envVariablesCheck(["CEP_USER_POOL_ID"]))
  .use(httpHeaderNormalizer({ canonical: true }))
  // .use(myHandler())
  // .use(httpJsonBodyParser())
  // .use(injectLambdaContext(Logger.jsonLogger, { clearState: true }));


// module.exports = { myHandler };
export { handler };

// Remove this call when you deploy the function on Lambda
const localTestRun = async () => {
    const rsp = await handler({}, {});
    console.log("Done");
}

localTestRun();
// Remove this call.

