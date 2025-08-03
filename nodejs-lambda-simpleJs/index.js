'use strict';

// flush with a bounded timeout so your Lambda doesn't hang forever
async function flushLogs(provider, timeoutMs) {
    return Promise.race([
        provider.shutdown(), // triggers immediate export of pending logs
        new Promise((_, reject) =>
            setTimeout(() => reject(new Error('forceFlush timed out')), timeoutMs)
        )
    ]);
}

async function flushLogger() {
    try {
        const { logs } = require('@opentelemetry/api-logs');
        const globalLoggerProvider = logs.getLoggerProvider();
        await flushLogs(globalLoggerProvider, 3000); // e.g., 3 seconds
    } catch (err) {
        console.warn('forceFlush failed or timed out:', err);
    }
}

const autoInstrumentationTest = async () => {
    const autoMain = require('./initOTelAuto');

    // const { context, diag, trace, DiagConsoleLogger, DiagLogLevel, SpanStatusCode } = require('@opentelemetry/api');
    // diag.setLogger(new DiagConsoleLogger(), DiagLogLevel.ALL);

    // const logTestFn = require('./tests/logTest');
    // logTestFn();

    const traceTestFn = require('./tests/traceTest');
    await traceTestFn();

    await flushLogger();

    const contextTest = require("./context-test");
    console.log(`The End`);
};

async function handler(event, context) {

    console.info('xyxyxy Start serving lambda request.');

    const paramEvent = "param-event:\r\n\r\n" + JSON.stringify(event, null, 2) + "\r\n\r\n";
    const paramContext = "param-context:\r\n\r\n" + JSON.stringify(context, null, 2) + "\r\n\r\n";

    await autoInstrumentationTest();

    const response = {
        statusCode: 200,
        body: ("\r\n\r\n" + paramEvent + paramContext)
    };
    return response;
}

module.exports = { handler };

// handler({ key1: 'value1', key2: 'value2' }, { /* context object */ });



