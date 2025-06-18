const { context, trace } = require('@opentelemetry/api');

const { S3Client, ListBucketsCommand } = require("@aws-sdk/client-s3");

const callAwsS3 = async (event) => {

    console.log("we are using node.js common module file.");

  let s3CmdSucceeded = true;
  let buckets = "";

  console.log(`sdkv3: handling /aws-sdk-call with S3 call.`);
  try {
      const s3Client = new S3Client();
      const command = new ListBucketsCommand({});
      await s3Client.send(command)
          .then(function (data) {
            s3CmdSucceeded = true;
            console.log(`${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}`);
            console.log(data.Buckets);
            buckets = data.Buckets.map((bucket) => bucket.Name).join(", ");
          })
          .catch(function (err) {
              console.error(`Error in aws-sdk-call:  ${err.message}`);
              s3CmdSucceeded = false;
          });
  }
  catch (err) {
      console.error(`error found in S3 call: ${err?.message || err}`);
      s3CmdSucceeded = false;
  }
  return { 'response': s3CmdSucceeded,
"allBuckets": buckets};
}



async function doWorkS3Call( tracer) {
    const ctx = context.active();
    const span = tracer.startSpan('BAZ-do-Work-S3-Call', {
        // kind: SpanKind.SERVER
    }, ctx);

    // simulate some random work.
    for (let i = 0; i <= Math.floor(Math.random() * 40000000); i += 1) {
        // empty
    }

    // Set attributes to the span.
    span.setAttribute('color', 'green');

    // Annotate our span to capture metadata about our operation
    span.addEvent('invoking doWork');
    const newContext = trace.setSpan(context.active(), span);
    let retVal = "";
    await context.with(newContext, async () => {
        retVal = await callAwsS3();
    });

    span.end();
    return retVal;
}

module.exports = { doWorkS3Call };
