print("MCP Server Foo, wait for debugger...!")

import os
if os.getenv("DEBUGPY_WAIT_FOR_CLIENT") == "1":
    import debugpy
    debugpy.listen(5678)
    print("Waiting for debugger attach on port 5678...")
    debugpy.wait_for_client()
    print("Debugger attached!")

print("Start running MCP Server Foo...!")

try:
    from mcp_simple_tool.oteltest import otel_test_call, call_aws_sdk, call_http
except ImportError:
    from oteltest import otel_test_call, call_aws_sdk, call_http

print("Test ADOT auto instrumenation...!")
# otel_test_call(3)
print("Completed testing ADOT auto instrumenation...!")

# import requests
# try:
#     response = requests.get("http://www.aws.com", timeout=5)
#     print(f"Status: {response.status_code}, Response time: {response.elapsed.total_seconds():.2f}s")
# except Exception as e:
#     print( f"!!! Error: {str(e)}")



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

@mcp.tool()
def callawssdk() -> str:
    """Call AWS SDK"""
    return call_aws_sdk()

@mcp.tool()
def pingweb(url: str) -> str:
    """Ping a web URL and return status"""
    return call_http()

# Add a dynamic greeting resource
@mcp.resource("greeting://{name}")
def get_greeting(name: str) -> str:
    """Get a personalized greeting"""
    return f"Hello, {name}!"

def main():
    mcp.run()

if __name__ == "__main__":
     main()