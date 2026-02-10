'use strict';

const { context, trace, ROOT_CONTEXT } = require('@opentelemetry/api');

const https = require('https');

function pingWebSite() {
    console.log(`Ping web site.`);

    return new Promise((resolve, reject) => {
        const httpReq = https.get('https://login.live-tst.com:44329', (httpResponse) => {
            console.log('Response status code:', httpResponse.statusCode);
            let data = "";
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


module.exports = async function main() {
    const tracer = trace.getTracer('contoso-tracer-node');
    const rootSpan = tracer.startSpan('Ping-Login-Website');
    const newContext = trace.setSpan(context.active(), rootSpan);
    await context.with(newContext, async () => {
        await pingWebSite();
    });

    // Be sure to end the span.
    rootSpan.end();
}

