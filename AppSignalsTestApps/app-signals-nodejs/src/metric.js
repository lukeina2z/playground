// metrics.js
const { metrics } = require('@opentelemetry/api');

// Get a meter from the global API
const meter = metrics.getMeter('my-meter');

// Create a counter (this works even if no SDK is registered)
const requestCounter = meter.createCounter('http_requests_total', {
  description: 'Counts the number of HTTP requests',
});

// Function to record a metric
function recordRequestMetric(route = '/unknown') {
  requestCounter.add(1, { route });
  console.log(`Metric "http_requests_total" incremented for route: ${route}`);
}

module.exports = { recordRequestMetric };
