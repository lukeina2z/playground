import { callS3, pingWebSite } from "./webapi.mjs"

export const myHandler = async (_event, _context) => {
    const responseA = await callS3();
    const responseB = await pingWebSite();

    let bodyMsg = "S3 call:\r\n\r\n" + responseA + "\r\n\r\n";
    bodyMsg = bodyMsg + "Ping web site:\r\n\r\n" + responseB;
    const response = {
        statusCode: 200,
        body: bodyMsg
    };
    return response;
};