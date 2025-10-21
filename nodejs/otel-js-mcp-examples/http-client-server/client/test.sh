#!/bin/bash

#
# Development script to run MCP client with OpenTelemetry instrumentation
# This script rebuilds and runs the client with OTLP trace export
#

# set -e

echo "Cleaning build artifacts..."
rm -rf ./build
rm -rf ./node_modules
rm -f ./package-lock.json

echo "Installing dependencies..."
npm install

echo "Building TypeScript..."
npm run build

echo "Starting MCP client with OpenTelemetry..."
OTEL_SERVICE_NAME=mcp-http-client \
  OTEL_TRACES_EXPORTER=otlp \
  OTEL_NODE_RESOURCE_DETECTORS="aws,env,host,os,process" \
  OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://127.0.0.1:4318/v1/traces \
  node --require @opentelemetry/auto-instrumentations-node/register ./build/client.js
