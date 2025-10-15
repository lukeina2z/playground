
1. Setup Python VEnv. 
    Python zero-code instrumentation  
    https://opentelemetry.io/docs/zero-code/python

    ```sh
    uv sync
    uv run opentelemetry-bootstrap -a install
    uv pip install -e /Users/lukezha/github/otel-python/pr-work/opentelemetry-python-contrib-mcp-pa/instrumentation-genai/opentelemetry-instrumentation-mcp

    uv pip list

    ```

1. Run MCP Client.

    ```sh

    OTEL_SERVICE_NAME=Mcp-Client-Cmd \
    OTEL_TRACES_EXPORTER=otlp \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4317/v1/traces \
    opentelemetry-instrument python ./main.py


    ```
