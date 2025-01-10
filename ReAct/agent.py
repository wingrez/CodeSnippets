import json
import os

with open("config.json") as f:
    config = json.load(f)

os.environ["OPENAI_API_KEY"] = config["OPENAI_API_KEY"]
os.environ["SERPAPI_API_KEY"] = config["SERPAPI_API_KEY"]
os.environ["LANGCHAIN_API_KEY"] = config["LANGCHAIN_API_KEY"]

from langchain import hub

prompt = hub.pull("hwchase17/react")
print("prompt:", prompt)

from langchain_openai import OpenAI

llm = OpenAI(base_url="https://api.deepseek.com/beta", model="deepseek-chat")

from langchain_community.utilities import SerpAPIWrapper
from langchain_core.tools import Tool

search = SerpAPIWrapper()

tools = [
    Tool(
        name="search",
        func=search.run,
        description="useful for when LLM needs to search the web for information",
    )
]

from langchain.agents import create_react_agent

agent = create_react_agent(llm, tools, prompt)

from langchain.agents import AgentExecutor

agent_executor = AgentExecutor(agent=agent, tools=tools, verbose=True)
agent_executor.invoke({"input": "Who is wingrez?"})
