console.log("start running sample code");

import { S3 } from '@aws-sdk/client-s3';

const s3 = new S3();

export const handler = async (_event, _context) => {
    console.info('Serving lambda request.');

    const result = await s3.listBuckets();

    console.log('Fetched OTel Resource Attrs:' + process.env.OTEL_RESOURCE_ATTRIBUTES);
    console.log('Fetched X-Ray Trace Header:' + process.env['_X_AMZN_TRACE_ID']);

    const bodyMsg = `Hello lambda - found ${result.Buckets?.length || 0} buckets. X-Ray Trace ID: ${process.env['_X_AMZN_TRACE_ID'] || 'Not available'}`;
    console.log(bodyMsg);

    const response = {
        statusCode: 200,
        body: bodyMsg
    };
    return response;
};

// await handler();
// console.log(`test completed.`);