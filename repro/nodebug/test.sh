#!/bin/bash

### OTel
# https://opentelemetry.io/docs/zero-code/js/
rm -fr ./build
rm -fr ./node_modules
rm ./package-lock.json

npm install
npm install --save @opentelemetry/api
npm install --save @opentelemetry/auto-instrumentations-node

npm run build

OTEL_SERVICE_NAME=otel-node-test \
  OTEL_NODE_RESOURCE_DETECTORS="env,host,os,process" \
  OTEL_TRACES_EXPORTER=otlp \
  OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4318/v1/traces \
  node --require @opentelemetry/auto-instrumentations-node/register ./build/index.js

