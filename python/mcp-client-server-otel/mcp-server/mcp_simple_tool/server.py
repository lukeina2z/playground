print("MCP Server Foo, wait for debugger...!")

import os
if os.getenv("DEBUGPY_WAIT_FOR_CLIENT") == "1":
    import debugpy
    debugpy.listen(5678)
    print("Waiting for debugger attach on port 5678...")
    debugpy.wait_for_client()
    print("Debugger attached!")

print("Start running MCP Server Foo...!")


import boto3
import requests

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
def pingweb() -> str:
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