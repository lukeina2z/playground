import asyncio
import os

from llama_index.core import VectorStoreIndex, SimpleDirectoryReader, Settings
from llama_index.core.agent.workflow import AgentWorkflow
from llama_index.llms.ollama import Ollama
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
from llama_index.core import StorageContext, load_index_from_storage

Settings.llm = Ollama(
    model="qwen3:30b-a3b",
    # model="mistral:7b",
    request_timeout = 360.0,
    context_window = 8000,
    temperature = 0.0,
)

Settings.embed_model = HuggingFaceEmbedding(model_name="BAAI/bge-base-en-v1.5")

storage_context = StorageContext.from_defaults(persist_dir="data/index")
index = load_index_from_storage(
    storage_context,
    embed_model = Settings.embed_model,
)

query_engine = index.as_query_engine(
    llm = Settings.llm,
)

async def search_otel_spans(query: str) -> str:
    """Useful for answering Open Telemetry span questions. Each element in the json file is a span."""
    response = await query_engine.aquery(query)
    return str(response)

agent = AgentWorkflow.from_tools_or_functions(
    [search_otel_spans],
    llm = Settings.llm,
    system_prompt = """You are an Open Telemetry trace expert that can analyze Open Telemetry spans .""",
)

async def main():
    response = await agent.run(
        "Search the span json files. How many Open Telemetry spans you can found?"
    )
    print(str(response))
   
    print("The End!")

if __name__ == "__main__":
    asyncio.run(main())
