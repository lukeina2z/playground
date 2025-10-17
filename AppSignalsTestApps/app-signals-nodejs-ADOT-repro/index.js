const awsCalls = require('./awsS3Test');

async function callWithOTelApi() {
  const { context, trace, ROOT_CONTEXT } = require('@opentelemetry/api');
  const tracer = trace.getTracer('great-tracer');
  const rootSpan = tracer.startSpan('NodeJs-ADOT-Root-Span');
  const newContext = trace.setSpan(context.active(), rootSpan);
  await context.with(newContext, async () => {
    for (let i = 0; i < 60; i += 1) {
      await awsCalls.s3Call();
    }
  });
  rootSpan.end();
}


async function callWithoutOTelApi() {
  for (let i = 0; i < 60; i += 1) {
    await awsCalls.s3Call();
  }
}


callWithOTelApi();

// callWithoutOTelApi()

