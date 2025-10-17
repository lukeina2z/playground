#!/bin/bash

npm uninstall  @opentelemetry/api
npm uninstall  @opentelemetry/auto-instrumentations-node
npm uninstall  @aws/aws-distro-opentelemetry-node-autoinstrumentation

rm -fr ./node_modules
rm ./package-lock.json

npm install --save  @opentelemetry/api
npm install --save @aws/aws-distro-opentelemetry-node-autoinstrumentation

npm install

# following https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Application-Signals-Enable-EC2Main.html#CloudWatch-Application-Signals-Enable-Other-instrument


OTEL_EXPORTER_OTLP_TRACES_TIMEOUT=3 \
OTEL_TRACES_EXPORTER="otlp,console" \
OTEL_METRICS_EXPORTER=none \
     OTEL_LOGS_EXPORTER=none \
     OTEL_AWS_APPLICATION_SIGNALS_ENABLED=true \
     OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
     OTEL_TRACES_SAMPLER=xray \
     OTEL_TRACES_SAMPLER_ARG="endpoint=http://localhost:2000" \
     OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT=http://localhost:4316/v1/metrics \
     OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
     OTEL_RESOURCE_ATTRIBUTES="service.name=ADOT-Nodejs-WithManualInstr" \
     node --require '@aws/aws-distro-opentelemetry-node-autoinstrumentation/register' index.js


