import json
import os
from openai import OpenAI

with open("config.json") as f:
    config = json.load(f)

os.environ["OPENAI_API_KEY"] = config["OPENAI_API_KEY"]

client = OpenAI(base_url="https://api.deepseek.com")

response = client.chat.completions.create(
    model="deepseek-chat",
    messages=[
        {"role": "user", "content": "Please introduce yourself."},
    ],
    stream=False,
)

print(response.choices[0].message.content)
