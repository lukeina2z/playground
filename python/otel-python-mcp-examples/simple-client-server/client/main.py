### Enable OTel logging
import logging
# logging.basicConfig(level=logging.DEBUG)


### ### ### Enable hook debugging
# https://opentelemetry.io/docs/zero-code/python/
# from opentelemetry.instrumentation.auto_instrumentation import initialize
# initialize()
### ### ###


import time

from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client
from pydantic import AnyUrl

from opentelemetry import trace

# Create server parameters for stdio connection
# server_params = StdioServerParameters(
#     command="./.venv/bin/opentelemetry-instrument",
#     args=["./.venv/bin/mcp", "run", "../server/mcp_simple_tool/server.py"],
#     env={
#         "OTEL_RESOURCE_ATTRIBUTES": "service.name=mcp-server",
#         "OTEL_EXPERIMENTAL_RESOURCE_DETECTORS":"host,os,process",
#         "OTEL_TRACES_EXPORTER": "otlp",
#         "OTEL_EXPORTER_OTLP_TRACES_ENDPOINT": "http://127.0.0.1:4317/v1/traces",
#     },
# )


server_params = StdioServerParameters(
    command="./.venv/bin/python",
    args=[
        # "-m", "debugpy", "--listen", "5678", "--wait-for-client",
        "./.venv/bin/mcp", "run", "../server/mcp_simple_tool/server.py"
    ],
    env={
        "OTEL_RESOURCE_ATTRIBUTES": "service.name=mcp-server",
        "OTEL_EXPERIMENTAL_RESOURCE_DETECTORS":"host,os,process",
        "OTEL_TRACES_EXPORTER": "otlp",
        "OTEL_EXPORTER_OTLP_TRACES_ENDPOINT": "http://127.0.0.1:4317/v1/traces",
    },
)


async def run():
    try:
        async with stdio_client(server_params) as (read, write):
            async with ClientSession(read, write) as session:
                # Initialize the connection
                await session.initialize()

                # Send notifications to the server
                print("SENDING NOTIFICATIONS")
                
                # Option 1: Log message notification
                # await session.send_log_message(level="info", data="Client connected and ready")
                
                # Option 2: Progress notification
                await session.send_progress_notification(
                    progress_token="client-init",
                    progress=50,
                    total=100
                )
                
                # Option 3: Resource list changed notification
                # await session.send_resource_list_changed()

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
                _ = await session.read_resource(AnyUrl("greeting://hello"))

                # Call pingweb tool
                print("CALL PINGWEB TOOL")
                result = await session.call_tool(
                    "pingweb", arguments={"url": "http://www.aws.com"}
                )
                print(result.content)

                # Call awssdkcall tool
                print("CALL AWSSDKCALL TOOL")
                result = await session.call_tool("awssdkcall")
                print(result.content)

                # Call a tool
                print("CALL TOOL")
                result = await session.call_tool(
                    "add", arguments={"a": 1, "b": 7}
                )
                print(result.content)

                # Give server time to flush traces before closing
                print("Waiting for server to flush traces...")
                time.sleep(3)
    except (OSError, ValueError) as exc:
        print(f"Client session ended: {exc}")
    except (Exception) as exc:
        print(f"Client session ended: {exc}")

if __name__ == "__main__":
    import asyncio

    tracer = trace.get_tracer(__name__)
    with tracer.start_as_current_span("mcp_client_main"):
        asyncio.run(run())
