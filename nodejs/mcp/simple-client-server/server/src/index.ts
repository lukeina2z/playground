import { McpServer, ResourceTemplate } from "@modelcontextprotocol/sdk/server/mcp.js";
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js";
import { z } from "zod";

import { makeHttpCall, makeS3Call } from "./testcall.js";



const fn = async ()=>{
  const retFoo = await makeHttpCall();
  const retBar = await makeS3Call();
  console.log(retFoo , retBar);
}

fn();

// Create an MCP server
const server = new McpServer({
  name: "Demo",
  version: "1.0.0"
});

// Add an addition tool
server.tool("add",
  { a: z.number(), b: z.number() },
  async ({ a, b }) => ({
    content: [{ type: "text", text: String(a + b) }]
  })
);

// Add an AWS SDK Call tool
server.tool("awssdkcall",
  { },
  async ({ }) => ({
    content: [{ type: "text", text: JSON.stringify(await makeS3Call()) }]
  })
);

// Add a dynamic greeting resource
server.resource(
  "file",
  new ResourceTemplate("file://{path}", { list: undefined }),
  async (uri, { path }) => ({
    contents: [{
      uri: uri.href,
      text: `File, ${path}!`
    }]
  })
);

server.prompt(
  "review-code",
  { code: z.string() },
  ({ code }) => ({
    messages: [{
      role: "user",
      content: {
        type: "text",
        text: `Please review this code:\n\n${code}`
      }
    }]
  })
);

// Start receiving messages on stdin and sending messages on stdout
const transport = new StdioServerTransport();
// await server.connect(transport);