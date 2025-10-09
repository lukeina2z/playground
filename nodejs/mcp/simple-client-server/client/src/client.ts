import { trace, context } from "@opentelemetry/api";
import { makeHttpCall, makeS3Call } from "./testcall.js";
import { Client } from "@modelcontextprotocol/sdk/client/index.js";
import { StdioClientTransport } from "@modelcontextprotocol/sdk/client/stdio.js";

const tracer = trace.getTracer('mcp-client');
const span = tracer.startSpan('mcp-client-operation');

await context.with(trace.setSpan(context.active(), span), async () => {
  const fn = async () => {
    const retFoo = await makeHttpCall();
    const retBar = await makeS3Call();
    console.log(retFoo, retBar);
  }

  await fn();

  const transport = new StdioClientTransport({
    command: "node",
    args: ["../server/build/index.js"]
  });

  const client = new Client(
    {
      name: "example-client",
      version: "1.0.0"
    }
  );

  await client.connect(transport);

  // List prompts
  const prompts = await client.listPrompts();

  // Get a prompt
  const prompt = await client.getPrompt({
    name: "review-code",
    arguments: {
      code: "console.log(\"hello\");"
    }
  });

  console.log("Prompt: ", prompt.messages[0].content);

  // List resources
  const resources = await client.listResources();
  for(let resource in resources.resources) {
    console.log("Resource: ", resource);
  }

  // List resource templates
  const templates = await client.listResourceTemplates();
  for(let template of templates.resourceTemplates) {
    console.log("Resource template: ", template.name);
  }

  // Call a tool
  const result = await client.callTool({
    name: "add",
    arguments: {
      a: 1,
      b: 8
    }
  });

  console.log("Tool result: ", result);
});

span.end();