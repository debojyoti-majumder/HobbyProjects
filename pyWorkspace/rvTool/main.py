from fastapi import FastAPI

app = FastAPI()

# Install dependency pip install "fastapi[standard]"
# To run the application use `fastapi dev main.py`
# API Endpoint is in http://127.0.0.1:8000

@app.get("/")
async def root():
    return {"message":"Hello FastAPI"}
