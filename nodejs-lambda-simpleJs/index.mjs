// import { myHandler } from './src/autoInstrumentOnly.mjs';
import { myHandler } from './src/otel.mjs';

import loggerTest from "./src/LoggerTest.mjs"

export async function handler(event, context) {

    console.info('xyxyxy Start serving lambda request.');

    loggerTest();

    const paramEvent = "param-event:\r\n\r\n" + JSON.stringify(event, null, 2) + "\r\n\r\n";
    const paramContext = "param-context:\r\n\r\n" + JSON.stringify(context, null, 2) + "\r\n\r\n";

    let retObj = await myHandler(event, context);

    retObj.body += ("\r\n\r\n" + paramEvent + paramContext);
    // return "xxx";
    return retObj;
}

handler({ key1: 'value1', key2: 'value2' }, { /* context object */ });

