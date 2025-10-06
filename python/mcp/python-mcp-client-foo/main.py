from mcp import ClientSession, StdioServerParameters, types
from mcp.client.stdio import stdio_client

# Create server parameters for stdio connection
server_params = StdioServerParameters(
    command="opentelemetry-instrument",  # Executable
    args=["./v-adot/bin/mcp", "run", "../python-mcp-server-foo/mcp_simple_tool/server.py"],  # Optional command line arguments
    env={
        # "MCP_LOG_LEVEL": "DEBUG",
        "DEBUGPY_WAIT_FOR_CLIENT": "0",
        "OTEL_SERVICE_NAME": "mcp-server-foo-LaunchByClient-CLI",
        "OTEL_LOG_LEVEL": "debug",
        "OTEL_METRICS_EXPORTER": "none",
        "OTEL_LOGS_EXPORTER": "none",
        "OTEL_AWS_APPLICATION_SIGNALS_ENABLED": "true",
        "OTEL_PYTHON_DISTRO": "aws_distro",
        "OTEL_PYTHON_CONFIGURATOR": "aws_configurator",
        # "OTEL_EXPORTER_OTLP_PROTOCOL": "http/protobuf",
        "OTEL_EXPORTER_OTLP_PROTOCOL": "grpc",
        "OTEL_TRACES_SAMPLER": "xray",
        "OTEL_TRACES_SAMPLER_ARG": "endpoint=http://localhost:2000",
        "OTEL_AWS_APPLICATION_SIGNALS_EXPORTER_ENDPOINT": "http://localhost:4316/v1/metrics",
        # "OTEL_EXPORTER_OTLP_TRACES_ENDPOINT": "http://localhost:4316/v1/traces",
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

            # Call a tool
            print("CALL TOOL")
            result = await session.call_tool("add", arguments={"a": 1, "b": 7})
            print(result.content)


if __name__ == "__main__":
    import asyncio

    asyncio.run(run())


# def main():
#     print("Hello from python-mcp-client-foo!")


# if __name__ == "__main__":
#     main()
