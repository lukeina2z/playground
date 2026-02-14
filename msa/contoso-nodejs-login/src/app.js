'use strict';

const { context, trace, ROOT_CONTEXT } = require('@opentelemetry/api');

const https = require('https');

function pingWebSite(url) {
    console.log(`Ping web site: ${url}  at ${new Date().toISOString()}  `);

    return new Promise((resolve, reject) => {
        const httpReq = https.get(url, (httpResponse) => {
            console.log('Response status code:', httpResponse.statusCode, `for url: ${url}`);
            let data = "";
            httpResponse.on('data', (chunk) => {
                data += chunk;  // Accumulate the chunks of data
            });

            httpResponse.on('end', () => {
                // console.log(`Response body: ${data}`);
                resolve(data);
            });
        });

        httpReq.on('error', (error) => {
            console.error(`Error in outgoing-http-call:  ${error.message} for url: ${url}`);
            reject(error);
        });
    });
};




async function PingLoginProbe() {
    const url = 'https://login.live-tst.com:44329/probe.srf';
    const tracer = trace.getTracer('Contoso-Nodejs');
    const rootSpan = tracer.startSpan('Ping-Login-Probe');
    const newContext = trace.setSpan(context.active(), rootSpan);
    await context.with(newContext, async () => {
        await pingWebSite(url);
    });

    // Be sure to end the span.
    rootSpan.end();
}


async function PingLogin() {
    const url = 'https://login.live-tst.com:44329';
    const tracer = trace.getTracer('Contoso-Nodejs');
    const rootSpan = tracer.startSpan('Ping-Login-Website');
    const newContext = trace.setSpan(context.active(), rootSpan);
    await context.with(newContext, async () => {
        await pingWebSite(url);
    });

    // Be sure to end the span.
    rootSpan.end();
}



module.exports = async function main() {

    await PingLoginProbe();

    await PingLogin();
}

