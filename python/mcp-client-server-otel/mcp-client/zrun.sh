#!/bin/bash

### OTel

    OTEL_SERVICE_NAME=mcp-client-PyShell \
    OTEL_TRACES_EXPORTER=otlp \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4317/v1/traces \
    uv run opentelemetry-instrument python ./main.py
