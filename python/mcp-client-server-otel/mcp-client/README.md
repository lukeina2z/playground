
1. Setup Python VEnv. 
    Python zero-code instrumentation  
    https://opentelemetry.io/docs/zero-code/python

    ```sh
    python -m venv v-otel
    source ./v-otel/bin/activate
    pip install "mcp[cli]"
    pip install boto3
    pip install requests
    pip install debugpy

    pip install opentelemetry-distro opentelemetry-exporter-otlp

    opentelemetry-bootstrap -a install

    pip install -e /Users/lukezha/github/otel-python/pr-work/opentelemetry-python-contrib-mcp-pa/instrumentation-genai/opentelemetry-instrumentation-mcp


    ```

1. Run MCP Client.

    ```sh

    OTEL_SERVICE_NAME=Mcp-Client-Cmd \
    OTEL_TRACES_EXPORTER=otlp \
    OTEL_EXPORTER_OTLP_TRACES_ENDPOINT=http://xyz-jaeger-100:4317/v1/traces \
    opentelemetry-instrument python ./main.py


    ```
