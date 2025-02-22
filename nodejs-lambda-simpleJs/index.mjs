import { callS3, pingWebSite } from "./src/webapi.mjs"

export const handler = async (_event, _context) => {
    console.info('Serving lambda request.');

    const eventStr = JSON.stringify(_event, null, 2);
    console.log('Received xxxevent:', eventStr);
    let bodyMsg = "xxxEvent:\r\n\r\n" + eventStr + "\r\n\r\n";

    console.info('Calling S3.');
    const responseA = await callS3();

    console.info("Ping web site.")
    const responseB = await pingWebSite();

    bodyMsg = bodyMsg + "S3 call:\r\n\r\n" + responseA;
    bodyMsg = bodyMsg + "\r\n\r\n" + "Call web site:\r\n\r\n" + responseB;
    const response = {
        statusCode: 200,
        body: bodyMsg
    };
    return response;
};

// handler();