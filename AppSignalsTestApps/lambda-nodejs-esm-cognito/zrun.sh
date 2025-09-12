#!/usr/bin/env bash


# /Users/lukezha/github/otel-js/99bld/opentelemetry-js-contrib/packages/auto-instrumentations-node/package.json

DEBUG=* \
OTEL_METRICS_EXPORTER=none \
OTEL_LOG_LEVEL=all \
OTEL_LOGS_EXPORTER=console \
OTEL_AWS_APPLICATION_SIGNALS_ENABLED=true \
OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
OTEL_TRACES_SAMPLER=xray \
OTEL_TRACES_SAMPLER_ARG=endpoint=http://localhost:2000 \
OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT=http://localhost:4316/v1/metrics \
OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
OTEL_RESOURCE_ATTRIBUTES="service.name=hello-nodejs-a" \
OTEL_TRACES_EXPORTER="console,otlp" \
node  --import @aws/aws-distro-opentelemetry-node-autoinstrumentation/register --experimental-loader=@opentelemetry/instrumentation/hook.mjs  index.mjs


