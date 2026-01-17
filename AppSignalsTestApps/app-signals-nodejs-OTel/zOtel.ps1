$ErrorActionPreference = "Stop"

# Clear NODE_OPTIONS to avoid preloading during installs
if ($env:NODE_OPTIONS) {
	Remove-Item Env:NODE_OPTIONS
}

# # Uninstall packages
# npm uninstall @opentelemetry/api
# npm uninstall @opentelemetry/auto-instrumentations-node
# npm uninstall @aws/aws-distro-opentelemetry-node-autoinstrumentation

# # Clean dependencies
# Remove-Item -Path "./node_modules" -Recurse -Force -ErrorAction SilentlyContinue
# Remove-Item -Path "./package-lock.json" -Force -ErrorAction SilentlyContinue

# # Reinstall packages
# npm install --save @opentelemetry/api
# npm install --save @opentelemetry/auto-instrumentations-node

npm install

# Set environment variables and run
$env:OTEL_LOG_LEVEL = "all"
$env:OTEL_TRACES_EXPORTER = "otlp"
$env:OTEL_EXPORTER_OTLP_ENDPOINT = "http://127.0.0.1:4318"
$env:OTEL_NODE_RESOURCE_DETECTORS = "env,host,os,process"
$env:OTEL_SERVICE_NAME = "OTel-Nodejs"
$env:NODE_OPTIONS = "--require @opentelemetry/auto-instrumentations-node/register"

node index.js
