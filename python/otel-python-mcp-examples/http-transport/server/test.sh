#!/bin/bash


OTEL_SERVICE_NAME=mcp-http-server \
  OTEL_EXPERIMENTAL_RESOURCE_DETECTORS="host,os,process" \
  OTEL_TRACES_EXPORTER=otlp \
  OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4317/v1/traces \
  uv run opentelemetry-instrument python ./server.py

  