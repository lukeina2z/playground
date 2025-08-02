'use strict';

const { context, trace, ROOT_CONTEXT } = require('@opentelemetry/api');
const awsCalls = require('./awsCall');

async function doWork(parent, tracer) {
    // Start another span. In this example, the main method already started a
    // span, so that'll be the parent span, and this will be a child span.
    const ctx = trace.setSpan(context.active(), parent);
    const span = tracer.startSpan('doWork', undefined, ctx);

    // simulate some random work.
    for (let i = 0; i <= Math.floor(Math.random() * 40000000); i += 1) {
        // empty
    }

    // Set attributes to the span.
    span.setAttribute('color', 'green');

    // Annotate our span to capture metadata about our operation
    span.addEvent('invoking doWork');

    const newContext = trace.setSpan(context.active(), span);

    await context.with(newContext, async () => {
        await awsCalls.s3Call();
    });

    context.with(newContext, () => {
        openFooFromProfileSync();
    });

    span.end();
}

module.exports = async function runTest() {
    const tracer = trace.getTracer('example-basic-tracer-node');
    // Create a span. A span must be closed.
    const parentSpan = tracer.startSpan('main');
    for (let i = 0; i < 1; i += 1) {
        await doWork(parentSpan, tracer);
    }
    // Be sure to end the span.
    parentSpan.end();
}

const fs = require('fs');
const path = require('path');
const os = require('os');

function openFooFromProfileSync() {
    const homeDir = os.homedir();
    const filePath = path.join(homeDir, 'foo.txt');

    try {
        const data = fs.readFileSync(filePath, 'utf8');
        console.log(`File contents:\n${data}`);
    } catch (err) {
        console.error(`Failed to open file: ${err.message}`);
    }
}

function openFooFromProfileAsync() {
    // Get the user's home directory (e.g., /Users/your-username)
    const homeDir = os.homedir();

    // Construct full path to foo.txt
    const filePath = path.join(homeDir, 'foo.txt');

    // Read the file
    fs.readFile(filePath, 'utf8', (err, data) => {
        if (err) {
            console.error(`Failed to open file: ${err.message}`);
            return;
        }
        console.log(`File contents:\n${data}`);
    });
}
