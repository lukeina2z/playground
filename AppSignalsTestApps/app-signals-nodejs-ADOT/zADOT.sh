#!/bin/bash


npm uninstall  @opentelemetry/api
npm uninstall  @opentelemetry/auto-instrumentations-node
npm uninstall  @aws/aws-distro-opentelemetry-node-autoinstrumentation

rm -fr ./node_modules
rm ./package-lock.json

npm install @aws/aws-distro-opentelemetry-node-autoinstrumentation

npm install


# OTEL_LOG_LEVEL=all \
#     OTEL_BSP_SCHEDULE_DELAY=1 \
#     OTEL_BSP_MAX_QUEUE_SIZE=1 \
#     OTEL_NODE_RESOURCE_DETECTORS="env,host,os,process" \
#     OTEL_TRACES_EXPORTER="otlp,console" \
#     OTEL_METRICS_EXPORTER=none \
#     OTEL_LOGS_EXPORTER=none \
#     OTEL_AWS_APPLICATION_SIGNALS_ENABLED=true \
#     OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
#     OTEL_TRACES_SAMPLER="xray" \
#     OTEL_TRACES_SAMPLER_ARG="endpoint=http://localhost:2000" \
#     OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT=http://localhost:4316/v1/metrics \
#     OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
#     OTEL_RESOURCE_ATTRIBUTES="service.name=OTel-Nodejs" \
#     node --require '@aws/aws-distro-opentelemetry-node-autoinstrumentation/register' index.js

OTEL_LOG_LEVEL=all \
OTEL_METRICS_EXPORTER=none \
     OTEL_BSP_SCHEDULE_DELAY=1 \
     OTEL_BSP_MAX_QUEUE_SIZE=1 \
    OTEL_LOGS_EXPORTER=none \
    OTEL_AWS_APPLICATION_SIGNALS_ENABLED=true \
    OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
    OTEL_TRACES_SAMPLER=xray \
    OTEL_TRACES_SAMPLER_ARG="endpoint=http://localhost:2000" \
    OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT=http://localhost:4316/v1/metrics \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
    OTEL_RESOURCE_ATTRIBUTES="service.name=xxyyzz" \
    node --require '@aws/aws-distro-opentelemetry-node-autoinstrumentation/register' index.js







