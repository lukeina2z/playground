import { callS3, pingWebSite } from "./src/webapi.mjs"

export const handler = async (_event, _context) => {
    console.info('Serving lambda request.');

    console.info('Calling S3.');
    const responseA = await callS3();

    console.info("Ping web site.")
    const responseB = await pingWebSite();

    let bodyMsg = "S3 call:\r\n\r\n" + responseA + "\r\n\r\n";
    bodyMsg = bodyMsg + "Ping web site:\r\n\r\n" + responseB;
    const response = {
        statusCode: 200,
        body: bodyMsg
    };
    return response;
};

// handler();