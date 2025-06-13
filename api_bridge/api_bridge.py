import subprocess
from fastapi import FastAPI

app = FastAPI()

C_EXEC = "C:/Users/¼­¹Î°æ/Poke_game/x64/Debug/backend_c.exe"

@app.get("/battle")
def run_battle():
    try:
        result = subprocess.run(C_EXEC, capture_output=True, text=True, check=True)
        return {"status": "ok", "output": result.stdout}
    except subprocess.CalledProcessError as e:
        return {"status": "error", "error": e.stderr}
