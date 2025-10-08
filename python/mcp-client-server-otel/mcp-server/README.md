
## Run the MCP Server

```sh
uvx --force-reinstall --from ../python-mcp-server-foo mcp-server-foo

uv run mcp-server-foo

uv run mcp dev ./mcp_simple_tool/server.py

```

## Run th MCP Server with ADOT

1. Setup Python VEnv. 
   https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Application-Signals-Enable-EC2Main.html#CloudWatch-Application-Signals-Enable-Other-instrument

    ```sh
    python -m venv v-adot
    source ./v-adot/bin/activate
    pip install "mcp[cli]"
    pip install boto3

    # pip install aws-opentelemetry-distro

    pip install -e /Users/lukezha/github/otel-python/pr-work/aws-otel-python-instrumentation-mcp/aws-opentelemetry-distro

    ```

1. Run MCP Server with ADOT.

    ```sh

    OTEL_LOG_LEVEL=all \
    OTEL_METRICS_EXPORTER=none \
    OTEL_LOGS_EXPORTER=none \
    OTEL_AWS_APPLICATION_SIGNALS_ENABLED=true \
    OTEL_PYTHON_DISTRO=aws_distro \
    OTEL_PYTHON_CONFIGURATOR=aws_configurator \
    # OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
    OTEL_TRACES_SAMPLER=xray \
    OTEL_TRACES_SAMPLER_ARG="endpoint=http://localhost:2000" \
    OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT=http://localhost:4316/v1/metrics \
    # OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4317/v1/traces \
    OTEL_RESOURCE_ATTRIBUTES="service.name=mcp-server-foo" \
    opentelemetry-instrument python ./mcp_simple_tool/server.py



    ```



