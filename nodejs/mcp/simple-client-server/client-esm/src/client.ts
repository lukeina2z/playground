import { trace, context } from "@opentelemetry/api";
import { makeHttpCall, makeS3Call, testOpenAIChat } from "./testcall.js";
import { Client } from "@modelcontextprotocol/sdk/client/index.js";
import { StdioClientTransport } from "@modelcontextprotocol/sdk/client/stdio.js";

const myMain = async () => {

  const tracer = trace.getTracer('mcp-client');
  const span = tracer.startSpan('mcp-client-operation');

  await context.with(trace.setSpan(context.active(), span), async () => {
    const fn = async () => {
      const retFoo = await makeHttpCall();
      const retBar = await makeS3Call();
      await testOpenAIChat();
      console.log(retFoo, retBar);
    }

    await fn();

    const transport = new StdioClientTransport({
      cwd: "../server",
      command: process.execPath,
      args: [
        "--require",
        "@opentelemetry/auto-instrumentations-node/register",
        "build/index.js"],
      env: {
        ...process.env,
        "OTEL_SERVICE_NAME": "MCP-Server-CJS",
        // "DEBUG": "*",
        // "DEBUG_FD": "3",  // Write debug logs to file descriptor 3
        "OTEL_INSTRUMENTATION_MCP_DEBUG_LOG_FILE": "/tmp/mcp-server-instrumentation-debug.log",
        "OTEL_LOG_LEVEL": "debug",
        "OTEL_TRACES_EXPORTER": "otlp",
        "OTEL_EXPORTER_OTLP_TRACES_ENDPOINT": "http://xyz-jaeger-100:4318/v1/traces"
      },
      // stderr: "inherit"
    });

    const client = new Client(
      {
        name: "example-client",
        version: "1.0.0"
      }
    );

    await client.connect(transport);

    // List tools
    const tools = await client.listTools();
    console.log("Available tools:");
    for (let tool of tools.tools) {
      console.log("Tool:", tool.name, "-", tool.description);
    }

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
    for (let resource in resources.resources) {
      console.log("Resource: ", resource);
    }

    // List resource templates
    const templates = await client.listResourceTemplates();
    for (let template of templates.resourceTemplates) {
      console.log("Resource template: ", template.name);
    }

    const resultSdkCall = await client.callTool({
      name: "awssdkcall",
      arguments: {
      }
    });
    console.log("Tool AWSSdkCall result: ", resultSdkCall);

    const resultWebCall = await client.callTool({
      name: "pingweb",
      arguments: {
        url: "http://www.aws.com"
      }
    });
    console.log("Tool PingWeb result: ", resultWebCall);

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
};

myMain();