const { context, trace } = require('@opentelemetry/api');
const https = require("https");

function getRandomSeconds(max) {
    return Math.floor(Math.random() * Math.floor(max)) * 1000;
}
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}


function fetchHttp(url) {
    return new Promise((resolve, reject) => {
        const req = https.get(url, (res) => {
            let data = "";

            res.on("data", (chunk) => {
                data += chunk;
            });

            res.on("end", () => {
                resolve({ statusCode: res.statusCode, body: data });
            });
        });

        req.on("error", (err) => reject(err));
    });
}

const handler = async (event) => {
    //   if(getRandomSeconds(100) === 0) {
    //       throw new Error("Something went wrong.");
    //   }   
    const retVal = await fetchHttp("https://www.amazon.com");

    let wait_time = getRandomSeconds(5);
    await sleep(wait_time);
    return {
        'statusCode': retVal.statusCode,
        "body": retVal.body.slice(0, 30) + "..."
    };
};

async function doWorkHttpCall(tracer) {
    const ctx = context.active();
    const span = tracer.startSpan('BAZ-do-Work-HTTP-Call', {
        // kind: SpanKind.SERVER
    }, ctx);

    // Set attributes to the span.
    span.setAttribute('color', 'green');

    // Annotate our span to capture metadata about our operation
    span.addEvent('invoking doWork');
    const newContext = trace.setSpan(context.active(), span);
    let retVal = "";
    await context.with(newContext, async () => {
        retVal = await handler();
    });

    span.end();
    return retVal;
}

module.exports = { doWorkHttpCall };

