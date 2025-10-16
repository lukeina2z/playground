#!/bin/bash


uv sync

uv run opentelemetry-bootstrap -a install

uv run pip install -e \
  /Users/lukezha/github/otel-python/pr-work/opentelemetry-python-contrib-mcp-pa/instrumentation-genai/opentelemetry-instrumentation-mcp


OTEL_SERVICE_NAME=mcp-client \
    OTEL_EXPERIMENTAL_RESOURCE_DETECTORS="env,host,os,process" \
    OTEL_TRACES_EXPORTER=otlp \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4317/v1/traces \
    uv run opentelemetry-instrument python ./main.py

