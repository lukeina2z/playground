print("Start running MCP Server Foo...!")

# import debugpy
# debugpy.listen(5678)
# print("Waiting for debugger attach on port 5678...")
# debugpy.wait_for_client()
# print("Debugger attached!")

from mcp.server.fastmcp import FastMCP

# Create an MCP server
mcp = FastMCP("PythonMcpDemoFoo")

@mcp.tool()
def add(a: int, b: int) -> int:
    """Add two numbers"""
    return a + b

@mcp.tool()
def subtract(a: int, b: int) -> int:
    """Subtract two numbers"""
    return a - b


# Add a dynamic greeting resource
@mcp.resource("greeting://{name}")
def get_greeting(name: str) -> str:
    """Get a personalized greeting"""
    return f"Hello, {name}!"

def main():
    mcp.run()

if __name__ == "__main__":
    main()