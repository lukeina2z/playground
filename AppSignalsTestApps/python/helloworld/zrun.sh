#!bash

# pip install boto3
# pip install aws-opentelemetry-distro



OTEL_METRICS_EXPORTER=none \
OTEL_LOGS_EXPORTER=none \
OTEL_AWS_APPLICATION_SIGNALS_ENABLED=true \
OTEL_PYTHON_DISTRO=aws_distro \
OTEL_PYTHON_CONFIGURATOR=aws_configurator \
OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
OTEL_TRACES_SAMPLER=xray \
OTEL_TRACES_SAMPLER_ARG="endpoint=http://localhost:2000" \
OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT=http://localhost:4316/v1/metrics \
OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
OTEL_RESOURCE_ATTRIBUTES="service.name=python-temp2" \
opentelemetry-instrument python ./adot-test.py

# OTEL_METRICS_EXPORTER=none \
# OTEL_LOGS_EXPORTER=none \
# OTEL_AWS_APPLICATION_SIGNALS_ENABLED=true \
# OTEL_PYTHON_DISTRO=aws_distro \
# OTEL_PYTHON_CONFIGURATOR=aws_configurator \
# OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
# OTEL_TRACES_SAMPLER=always_on \
# OTEL_LOG_LEVEL=info \
# # OTEL_TRACES_SAMPLER_ARG="endpoint=http://localhost:2000" \
# # OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT=http://localhost:4316/v1/metrics \
# OTEL_TRACES_EXPORTER=otlp \
# # OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://100.21.71.227:4318/v1/traces \
# OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
# OTEL_RESOURCE_ATTRIBUTES="service.name=python-adot-demo" \
# opentelemetry-instrument python ./adot-test.py