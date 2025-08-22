from fastapi import FastAPI
from pydantic import BaseModel

from models import task
app = FastAPI()

# Install dependency pip install "fastapi[standard]"
# To run the application use `fastapi dev main.py`
# API Endpoint is in http://127.0.0.1:8000

class NewTask(BaseModel):
    caption:str

@app.get("/")
async def root():
    return {"message":"Hello FastAPI"}

@app.post("/task")
async def create_task(task:NewTask):
    return task
