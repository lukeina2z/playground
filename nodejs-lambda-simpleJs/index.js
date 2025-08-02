'use strict';

const autoInstrumentationTest = async () => {
    const autoMain = require('./initOTelAuto');

    // const { context, diag, trace, DiagConsoleLogger, DiagLogLevel, SpanStatusCode } = require('@opentelemetry/api');
    // diag.setLogger(new DiagConsoleLogger(), DiagLogLevel.ALL);

    // const logTestFn = require('./tests/logTest');
    // logTestFn();

    const traceTestFn = require('./tests/traceTest');
    await traceTestFn();

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

// module.exports = handler;

handler({ key1: 'value1', key2: 'value2' }, { /* context object */ });