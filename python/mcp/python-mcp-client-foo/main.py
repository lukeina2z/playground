from mcp import ClientSession, StdioServerParameters, types
from mcp.client.stdio import stdio_client

# Create server parameters for stdio connection
server_params = StdioServerParameters(
    command="./.venv/bin/mcp",  # Executable
    args=["run", "../python-mcp-server-foo/main.py"],  # Optional command line arguments
    env=None,  # Optional environment variables
)


# server_params = StdioServerParameters(
#     command="uvx",
#     args=[
#         "--from", "/Users/lukezha/github/playground/python/mcp/python-mcp-server-foo",
#         "python", "main.py"
#     ],
# )


# server_params = StdioServerParameters(
#     command="mcp",  # Executable
#     args=["run", "server.py"],  # Optional command line arguments
#     env=None,  # Optional environment variables
# )

# {
#   "mcpServers": {
#     "my-server": {
#       "command": "uvx",
#       "args": [
#         "--from", "/path/to/your/local/git/clone",
#         "--with", "opentelemetry-distro",
#         "--with", "opentelemetry-exporter-otlp",
#         "opentelemetry-instrument",
#         "python", "server.py"
#       ],
#       "env": {
#         "OTEL_SERVICE_NAME": "my-mcp-server",
#         "OTEL_EXPORTER_OTLP_ENDPOINT": "http://localhost:4318"
#       }
#     }
#   }
# }


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
