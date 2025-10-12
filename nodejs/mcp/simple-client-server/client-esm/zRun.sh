#!/bin/bash

### OTel

# https://opentelemetry.io/docs/zero-code/js

# https://github.com/open-telemetry/opentelemetry-js/blob/main/doc/esm-support.md

# npm install --save @opentelemetry/api
# npm install --save @opentelemetry/auto-instrumentations-node

rm -fr ./build
rm -fr ./node_modules

npm install

npm run build

  # OTEL_LOG_LEVEL=all \
  #   --experimental-loader=@opentelemetry/instrumentation/hook.mjs   \
  # OTEL_LOG_LEVEL=all \
  #   OTEL_NODE_RESOURCE_DETECTORS="aws,env,host,os" \

OTEL_SERVICE_NAME=MCP-Client-ESM \
  DEBUG=* \
  OTEL_NODE_RESOURCE_DETECTORS="env,host,os" \
  OTEL_INSTRUMENTATION_MCP_DEBUG_LOG_FILE=/tmp/mcp-client-instrumentation-debug.log \
  OTEL_TRACES_EXPORTER=otlp \
  OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4318/v1/traces \
  node  --experimental-loader=@opentelemetry/instrumentation/hook.mjs --import @opentelemetry/auto-instrumentations-node/register  \
  ./build/client.js
  

