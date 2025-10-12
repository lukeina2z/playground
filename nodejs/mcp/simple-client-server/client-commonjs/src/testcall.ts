import * as http from 'http';
import { S3Client, ListBucketsCommand } from "@aws-sdk/client-s3";

interface S3Response {
    response: boolean;
    allBuckets: string;
}

const pingS3 = async (): Promise<S3Response> => {
    let s3CmdSucceeded = true;
    let buckets = "";
    try {
        const s3Client = new S3Client();
        const command = new ListBucketsCommand({});
        const data = await s3Client.send(command);
        s3CmdSucceeded = true;
        buckets = data.Buckets?.map((bucket) => bucket.Name).join(", ") || "";
    } catch (err: any) {
        s3CmdSucceeded = false;
    }
    return {
        response: s3CmdSucceeded,
        allBuckets: buckets
    };
};

function pingWebSite(): Promise<string> {
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
            console.error(`Error in outgoing-http-call:  ${error.message}`);
            reject(error);
        });
    });
};

export async function makeS3Call(): Promise<String> {
    const ret = await pingS3();
    return `S3 Call Succeeded: ${ret.response}, Buckets: ${ret.allBuckets}`;
}

export async function makeHttpCall(): Promise<String> {
    const ret = await pingWebSite();
    return ret;
}


import OpenAI from "openai";
import * as dotenv from 'dotenv';

dotenv.config();


export async function testOpenAIChat(): Promise<void> {

    const openai = new OpenAI({
        apiKey: process.env.OPENAI_API_KEY,
    });

    async function runChat() {
        let response;
        try {
            response = await openai.chat.completions.create({
                model: "gpt-3.5-turbo",
                messages: [
                    { role: "system", content: "You are a helpful assistant." },
                    { role: "user", content: "Tell me a joke." }
                ]
            });
            runChat();
        } catch (err) {
            console.error("OpenAI Chat error: ", err);
        }

        console.log(response ? response.choices[0].message.content : "empty content");
    }

    runChat();
}

