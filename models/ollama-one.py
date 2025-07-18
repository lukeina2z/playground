
# Import the libraries
from langchain_ollama import ChatOllama
from langchain_core.messages import AIMessage

# Initialize the LLM. This is when we pick the model and the temperature (which controls the randomness of the output). llm is what we will use to call the model.
llm = ChatOllama(
    model="tinyllama:1.1b",
    temperature=0,  # 0 for more deterministic outputs
)

# We need to provide an array of messages to the model. The first message is always the system message, which tells the model what it is. The second message is the human message, which is what we want to ask the model.
messages = [
    (
        "system",
        "You are a helpful assistant",
    ),
    ("human", "I love programming."),
]

# Send the array of messages to the model and get the response. The response is an AIMessage object, which contains the content of the message. Which we will print below.
ai_msg = llm.invoke(messages)

# Display the response
print(ai_msg.content)

print("The End!")