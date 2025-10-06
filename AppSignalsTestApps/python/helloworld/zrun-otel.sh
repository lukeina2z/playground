#!/bin/bash

### OTel

# https://opentelemetry.io/docs/zero-code/python/
# python -m venv v-otel
# source ./v-otel/bin/activate
# pip install boto3
# pip install opentelemetry-distro opentelemetry-exporter-otlp
# opentelemetry-bootstrap -a install

OTEL_RESOURCE_ATTRIBUTES="service.name=python-otel-EnvVar" \
OTEL_TRACES_EXPORTER="otlp" \
OTEL_EXPORTER_OTLP_TRACES_ENDPOINT="http://xyz-jaeger-100:4317/v1/traces" \
opentelemetry-instrument python ./adot-test.py


# --exporter_otlp_traces_endpoint EXPORTER_OTLP_TRACES_ENDPOINT
# --exporter_otlp_traces_protocol EXPORTER_OTLP_TRACES_PROTOCOL
# --service_name SERVICE_NAME

# opentelemetry-instrument \
#     --traces_exporter otlp \
#     --service_name python-otel-cli-grpc \
#     --exporter_otlp_traces_protocol grpc \
#     --exporter_otlp_endpoint http://xyz-jaeger-100:4317/v1/traces \
#     python ./adot-test.py


### 4318 http with Jaeger is not working
# opentelemetry-instrument \
#     --traces_exporter otlp \
#     --service_name python-otel-cli-http \
#     --exporter_otlp_traces_protocol http/protobuf \
#     --exporter_otlp_endpoint http://xyz-jaeger-100:4318/v1/traces \
#     python ./adot-test.py