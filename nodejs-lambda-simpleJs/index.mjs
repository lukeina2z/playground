import { callS3, pingWebSite } from "./src/webapi.mjs"

export const handler = async (_event, _context) => {
    console.info('Serving lambda request.');

    console.info('Calling S3.');
    callS3();

    console.info("Ping web site.")
    pingWebSite();

    const response = {
        statusCode: 200,
        body: "Great Feature!"
    };
    return response;
};

handler();