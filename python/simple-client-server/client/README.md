
1. Setup virtual environment.

    ```sh
    python -m venv votel
    source ./votel/bin/activate
    pip install "mcp[cli]"
    pip install requests

    pip install opentelemetry-distro opentelemetry-exporter-otlp

    opentelemetry-bootstrap -a install

    pip install -e  /Users/lukezha/github/otel-python/pr-work/opentelemetry-python-contrib-mcp-prfoo/instrumentation-genai/opentelemetry-instrumentation-mcp

    ```

1. Run MCP Client.

    ```sh

    OTEL_SERVICE_NAME=Mcp-Client \
    OTEL_TRACES_EXPORTER=otlp \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4317/v1/traces \
    opentelemetry-instrument python ./main.py


    ```
