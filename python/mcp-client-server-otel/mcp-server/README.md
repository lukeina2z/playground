
## Run the MCP Server

```sh
uvx --force-reinstall --from . mcp-server-foo

uv run mcp-server-foo

uv run mcp dev ./mcp_simple_tool/server.py

```

## Run th MCP Server with OTel

1. Setup Python VEnv  
    Python zero-code instrumentation  
    https://opentelemetry.io/docs/zero-code/python

    ```sh
    python -m venv v-otel
    source ./v-otel/bin/activate
    pip install "mcp[cli]"
    pip install boto3
    pip install requests


    pip install opentelemetry-distro opentelemetry-exporter-otlp

    opentelemetry-bootstrap -a install

    # pip install -e /Users/lukezha/github/otel-python/pr-work/opentelemetry-python/opentelemetry-api

    # pip install -e /Users/lukezha/github/otel-python/pr-work/opentelemetry-python/opentelemetry-semantic-conventions

    # pip install -e /Users/lukezha/github/otel-python/pr-work/opentelemetry-python-contrib-mcp-pa/opentelemetry-instrumentation --no-deps

    # pip install -e /Users/lukezha/github/otel-python/pr-work/opentelemetry-python-contrib-mcp-pa/opentelemetry-distro --no-deps

    ```

1. Run MCP Server with OTel.

    ```sh

    # OTEL_LOG_LEVEL=all \
    # OTEL_METRICS_EXPORTER=none \
    # OTEL_LOGS_EXPORTER=none \
    # OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf \
    # OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://localhost:4316/v1/traces \
    # OTEL_RESOURCE_ATTRIBUTES="service.name=mcp-server-foo" \

    OTEL_SERVICE_NAME=Mcp-Server-Foo-PyCli \
    OTEL_TRACES_EXPORTER=otlp \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4317/v1/traces \
    opentelemetry-instrument python ./mcp_simple_tool/server.py



    ```



