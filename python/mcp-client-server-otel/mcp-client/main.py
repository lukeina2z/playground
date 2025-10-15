### Enable OTel logging
import logging
# logging.basicConfig(level=logging.DEBUG)


### ### ### Enable hook debugging
from opentelemetry.instrumentation.auto_instrumentation import initialize
initialize()
### ### ###


import boto3
import requests
import time
from opentelemetry import trace

s3 = boto3.resource("s3")

def call_aws_sdk():
    bucket_names = [bucket.name for bucket in s3.buckets.all()]
    return ",".join(bucket_names)

def call_http() -> str:
    try:
        response = requests.get("http://www.aws.com", timeout=120)
        return f"HTTP status code: {response.status_code}"
    except Exception as e:
        return f"Error: {str(e)}"

# call_aws_sdk()
# call_http()

from mcp import ClientSession, StdioServerParameters, types
from mcp.client.stdio import stdio_client

# Create server parameters for stdio connection
server_params = StdioServerParameters(
    command="./.venv/bin/opentelemetry-instrument",  # Executable
    args=["./.venv/bin/mcp", "run", "../mcp-server/mcp_simple_tool/server.py"],  # Optional command line arguments
    env={
        # "OTEL_SERVICE_NAME": "Mcp-Server-PyLaunchJson",
        "OTEL_RESOURCE_ATTRIBUTES": "service.name=mcp-server-Py",
        "OTEL_TRACES_EXPORTER": "otlp",
        "OTEL_EXPORTER_OTLP_TRACES_ENDPOINT": "http://xyz-jaeger-100:4317/v1/traces",
    },
)

# server_params = StdioServerParameters(
#     command="uvx",  # Executable
#     args=[
#         "--force-reinstall",
#         "--from", "../python-mcp-server-foo",
#         "--with", "aws-opentelemetry-distro",
#         "opentelemetry-instrument",
#         "mcp-server-foo"],  # Optional command line arguments
#     env={
#         # "MCP_LOG_LEVEL": "DEBUG",
#         "DEBUGPY_WAIT_FOR_CLIENT": "0",
#         "OTEL_SERVICE_NAME": "mcp-server-foo-LaunchByClient-UV",
#         "OTEL_LOG_LEVEL": "debug",
#         "OTEL_METRICS_EXPORTER": "none",
#         "OTEL_LOGS_EXPORTER": "none",
#         "OTEL_AWS_APPLICATION_SIGNALS_ENABLED": "true",
#         "OTEL_PYTHON_DISTRO": "aws_distro",
#         "OTEL_PYTHON_CONFIGURATOR": "aws_configurator",
#         "OTEL_EXPORTER_OTLP_PROTOCOL": "http/protobuf",
#         "OTEL_TRACES_SAMPLER": "xray",
#         "OTEL_TRACES_SAMPLER_ARG": "endpoint=http://localhost:2000",
#         "OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT": "http://localhost:4316/v1/metrics",
#         "OTEL_EXPORTER_OTLP_TRACES_ENDPOINT": "http://localhost:4316/v1/traces",
#     },
# )

async def run():
    try:
        async with stdio_client(server_params) as (read, write):
            async with ClientSession(
                read, write
            ) as session:
                # Initialize the connection
                await session.initialize()

                # List available resources
                resources = await session.list_resources()
                print("LISTING RESOURCES")
                for resource in resources:
                    print("Resource: ", resource)

                # List available tools
                tools = await session.list_tools()
                print("LISTING TOOLS")
                for tool in tools.tools:
                    print("Tool: ", tool.name)

                # Read a resource
                print("READING RESOURCE")
                content, mime_type = await session.read_resource("greeting://hello")

                # Call pingweb tool
                print("CALL PINGWEB TOOL")
                result = await session.call_tool("pingweb", arguments={"url": "http://www.aws.com"})
                print(result.content)

                # Call callawssdk tool
                print("CALL CALLAWSSDK TOOL")
                result = await session.call_tool("callawssdk")
                print(result.content)

                # Call a tool
                print("CALL TOOL")
                result = await session.call_tool("add", arguments={"a": 1, "b": 7})
                print(result.content)
                    
                # Give server time to flush traces before closing
                print("Waiting for server to flush traces...")
                time.sleep(3)
    except Exception as e:
        print(f"Client session ended: {e}")


if __name__ == "__main__":
    import asyncio
    
    tracer = trace.get_tracer(__name__)
    with tracer.start_as_current_span("mcp_client_main"):
        asyncio.run(run())


# def main():
#     print("Hello from python-mcp-client-foo!")


# if __name__ == "__main__":
#     main()
