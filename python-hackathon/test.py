import asyncio
from datetime import datetime
from llama_index.core.agent.workflow import FunctionAgent
from llama_index.llms.ollama import Ollama
from llama_index.core.llms import ChatMessage, MessageRole

from util import display_llm_response, get_single_sample_span

llm = Ollama(
        model = "qwen3:8b",
        # model = "qwen3:30b-a3b",
        temperature = 0.0,
        request_timeout = 360.0,
        context_window = 20000,
        thinking = False,
        stream = True,
         system_prompt="You are a helpful assistant that can analyze Open Telemetry trace span.",
)

async def main():
    print(datetime.now())
    span_json = get_single_sample_span()
    userPrompt = "Please analyze this Open Telemetry Trace spans. Here is the json document, each element of 'All spans' field is an open telemetry span.  "
    userPrompt += span_json

    stream = await llm.astream(
        [ChatMessage(role=MessageRole.USER, content=userPrompt)]
    )

    async for chunk in stream:
        print(chunk.delta, end="", flush=True)

    print("\n", datetime.now())
    print("The end")

if __name__ == "__main__":
    asyncio.run(main())

