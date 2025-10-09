#!/bin/bash

### OTel

# https://opentelemetry.io/docs/zero-code/js/

npm install --save @opentelemetry/api
npm install --save @opentelemetry/auto-instrumentations-node

npm run build

OTEL_SERVICE_NAME=Mcp-Client-zRun \
  OTEL_LOG_LEVEL=all \
  OTEL_TRACES_EXPORTER=otlp \
  OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4318/v1/traces \
  node --require @opentelemetry/auto-instrumentations-node/register ./build/index.js

