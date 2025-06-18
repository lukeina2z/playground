const { trace } = require('@opentelemetry/api');

const tracer = trace.getTracer('BAZ-lambda-tracer');

function getMyTracer() {
    return tracer;
}

module.exports = { getMyTracer };

