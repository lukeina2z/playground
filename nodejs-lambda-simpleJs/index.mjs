import webApp from "./src/webapi.mjs"

export const handler = async (_event, _context) => {
    console.info('Serving lambda request.');

    console.info('Calling S3.');


    console.info("Ping web site.")


    const response = {
        statusCode: 200,
        body: bodyMsg
    };
    return response;
};