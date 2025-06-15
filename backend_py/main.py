from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
import subprocess
import json

app = FastAPI()

C_EXEC_PATH = "C:/Users/cheab/source/repos/Poke_game/build/bin/Debug/poke_game.exe"

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/shop")
def get_shop():
    try:
        result = subprocess.run(
            [C_EXEC_PATH, "shop"],
            capture_output=True,
            text=True,
            encoding="utf-8",
            check=True,
            timeout=5
        )
        return json.loads(result.stdout)

    except subprocess.TimeoutExpired:
        raise HTTPException(status_code=500, detail="poke_game.exe 실행 타임아웃")

    except subprocess.CalledProcessError:
        raise HTTPException(status_code=500, detail="C 실행 실패")

    except json.JSONDecodeError:
        raise HTTPException(status_code=500, detail="C 프로그램 출력이 JSON 형식이 아님")


@app.get("/buy/{pokemon_id}")  # ✅ 추가된 buy API
def buy_pokemon(pokemon_id: int):
    try:
        result = subprocess.run(
            [C_EXEC_PATH, "buy", str(pokemon_id)],
            capture_output=True,
            text=True,
            encoding="utf-8",
            check=True,
            timeout=5
        )
        return json.loads(result.stdout)

    except subprocess.TimeoutExpired:
        raise HTTPException(status_code=500, detail="poke_game.exe 실행 타임아웃")

    except subprocess.CalledProcessError as e:
        raise HTTPException(status_code=500, detail="C 실행 실패")

    except json.JSONDecodeError:
        raise HTTPException(status_code=500, detail="C 프로그램 출력이 JSON 형식이 아님")

