#!/bin/bash

### OTel

# https://opentelemetry.io/docs/zero-code/js

# https://github.com/open-telemetry/opentelemetry-js/blob/main/doc/esm-support.md

npm install --save @opentelemetry/api
npm install --save @opentelemetry/auto-instrumentations-node

npm run build

  # OTEL_LOG_LEVEL=all \
  #   --experimental-loader=@opentelemetry/instrumentation/hook.mjs   \

OTEL_SERVICE_NAME=Mcp-Client-CJS-zRun \
  OTEL_TRACES_EXPORTER=otlp \
  OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4318/v1/traces \
  node  --import @opentelemetry/auto-instrumentations-node/register  \
  ./build/client.js
  
