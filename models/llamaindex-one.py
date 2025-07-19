import asyncio
from llama_index.llms.ollama import Ollama
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
from llama_index.core.workflow import Context
from llama_index.core.agent.workflow import FunctionAgent
from llama_index.llms.ollama import Ollama

# Define a simple calculator tool
def multiply(a: float, b: float) -> float:
    """Useful for multiplying two numbers."""
    return a * b

# Create an agent workflow with our calculator tool
agent = FunctionAgent(
    tools=[multiply],
    llm = Ollama(
        model="llama3.1",
        request_timeout=360.0,
        # Manually set the context window to limit memory usage
        context_window=8000,
    ),
    system_prompt="You can chat with user. You are a helpful assistant that can multiply two numbers.",
)

async def main():
    # create context
    ctx = Context(agent)
    # run agent with context
    response = await agent.run("My name is Logan", ctx=ctx)
    print(str(response))
    # Run the agent
    response = await agent.run("What is 1234 * 4567?", ctx = ctx)
    print(str(response))
    response = await agent.run("What is my name?", ctx=ctx)
    print(str(response))
    
    print("The End!")

# Run the agent
if __name__ == "__main__":
    asyncio.run(main())