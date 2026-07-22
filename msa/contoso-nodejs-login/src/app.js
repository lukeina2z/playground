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


async function PingSapiProbe() {
    const url = 'https://api.login.live-tst.com:44404/probe.srf';
    const tracer = trace.getTracer('Contoso-Nodejs');
    const rootSpan = tracer.startSpan('Ping-Sapi-Probe');
    const newContext = trace.setSpan(context.active(), rootSpan);
    await context.with(newContext, async () => {
        await pingWebSite(url);
    });

    // Be sure to end the span.
    rootSpan.end();
}


async function PingSapiInfo() {
    const url = 'https://api.login.live-tst.com:44404/info.srf';
    const tracer = trace.getTracer('Contoso-Nodejs');
    const rootSpan = tracer.startSpan('Ping-Sapi-Info');
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



async function simulateTraffic(fastMode = false) {
    const volumeMultiplier = fastMode ? 5 : 1;
    const delayDivisor = fastMode ? 5 : 1;
    const minDelayMs = Math.max(1, Math.floor(200 / delayDivisor));
    const maxDelayMs = Math.max(minDelayMs, Math.floor(3000 / delayDivisor));
    const burstChance = 0.25;       // 25% chance of a burst
    const burstMinCount = 3 * volumeMultiplier;
    const burstMaxCount = 8 * volumeMultiplier;
    const sessionCount = (Math.floor(Math.random() * 5) + 1) * volumeMultiplier; // 1-5 sessions per cycle

    console.log(`\n--- Traffic cycle started at ${new Date().toISOString()} | sessions: ${sessionCount} ---`);

    for (let session = 0; session < sessionCount; session++) {
        const sessionDelay = Math.floor(Math.random() * (maxDelayMs - minDelayMs)) + minDelayMs;
        const isBurst = Math.random() < burstChance;
        const requestCount = isBurst
            ? Math.floor(Math.random() * (burstMaxCount - burstMinCount)) + burstMinCount
            : 1;

        console.log(`  Session ${session + 1}/${sessionCount} — requests: ${requestCount}, burst: ${isBurst}`);

        for (let r = 0; r < requestCount; r++) {
            try {
                await PingLoginProbe();
            } catch (err) {
                console.error(`  Probe request error: ${err.message}`);
            }

            const jitter = Math.floor(Math.random() * Math.max(1, Math.floor(500 / delayDivisor)));
            await new Promise(resolve => setTimeout(resolve, jitter));

            try {
                await PingLogin();
            } catch (err) {
                console.error(`  Login request error: ${err.message}`);
            }

            try {
                await PingSapiProbe();
            } catch (err) {
                console.error(`  SAPI probe request error: ${err.message}`);
            }

            const sapiJitter = Math.floor(Math.random() * Math.max(1, Math.floor(500 / delayDivisor)));
            await new Promise(resolve => setTimeout(resolve, sapiJitter));

            try {
                await PingSapiInfo();
            } catch (err) {
                console.error(`  SAPI info request error: ${err.message}`);
            }

            if (r < requestCount - 1) {
                const gap = Math.floor(Math.random() * Math.max(1, Math.floor(400 / delayDivisor))) + Math.max(1, Math.floor(50 / delayDivisor));
                await new Promise(resolve => setTimeout(resolve, gap));
            }
        }

        if (session < sessionCount - 1) {
            await new Promise(resolve => setTimeout(resolve, sessionDelay));
        }
    }

    console.log(`--- Traffic cycle finished at ${new Date().toISOString()} ---\n`);
}

module.exports = { runOnceTest: async function main() {

    await PingLoginProbe();

    // await PingLogin();
}, simulateTraffic };

