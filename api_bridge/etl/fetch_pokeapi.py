"""
fetch_pokeapi.py
────────────────────────────────────────────────────────────
PokeAPI → MariaDB( poke_game )  ETL 스크립트
테이블: pokemon, move, pokemon_move  (player_pokemon 은 영향 X)

실행 전:
    pip install requests pymysql python-dotenv tqdm
────────────────────────────────────────────────────────────
"""

import os, sys, logging, requests, pymysql
from typing import List, Dict, Tuple, Optional
from dotenv import load_dotenv
from tqdm import tqdm

# ─────────────────── 0. 설정 & 로깅 ───────────────────
ROOT = os.path.dirname(os.path.dirname(__file__))          # api_bridge/
load_dotenv(os.path.join(ROOT, ".env"))

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s | %(levelname)s | %(message)s",
    handlers=[logging.StreamHandler(sys.stdout)],
)

DB = {
    "host": "localhost",
    "port": 13306,
    "user": os.getenv("DB_USER", "root"),
    "password": os.getenv("DB_PASS", "1234"),
    "database": "poke_game",
    "charset": "utf8mb4",
    "autocommit": False,           # 트랜잭션 수동
}

POKEMONS = [
    "pikachu", "charizard", "bulbasaur", "squirtle",
    "mew", "mewtwo", "snorlax", "eevee", "gengar", "lucario"
]
NUM_MOVES = 4   # 슬롯 1~4 까지만 저장


# ─────────────────── 1. PokeAPI helpers ───────────────────
def fetch_pokemon(name: str) -> Optional[Tuple[Dict, List[Dict]]]:
    """포켓몬 1마리 & 기술 목록 반환; 실패 시 None"""
    url = f"https://pokeapi.co/api/v2/pokemon/{name.lower()}"
    r = requests.get(url, timeout=10)
    if r.status_code != 200:
        logging.warning("skip %-10s : %s", name, r.status_code)
        return None

    data  = r.json()
    stats = {s["stat"]["name"]: s["base_stat"] for s in data["stats"]}
    moves = data["moves"][:NUM_MOVES]

    pokemon_row = dict(
        id        = data["id"],
        name      = name,
        hp        = stats["hp"],
        attack    = stats["attack"],
        defense   = stats["defense"],
        speed     = stats["speed"],
        image_url = data["sprites"]["other"]["official-artwork"]["front_default"],
    )

    move_rows: List[Dict] = []
    for slot, mv in enumerate(moves, start=1):
        mv_detail = requests.get(mv["move"]["url"], timeout=5).json()
        move_rows.append(dict(
            id    = mv_detail["id"],
            name  = mv_detail["name"],
            power = mv_detail.get("power") or 0,
            slot  = slot,
        ))
    return pokemon_row, move_rows


# ─────────────────── 2. DB Upsert helpers ───────────────────
def upsert(cur, table: str, row: Dict, update_cols: List[str] | None = None):
    """INSERT ... ON DUPLICATE KEY UPDATE"""
    cols = ", ".join(row.keys())
    ph   = ", ".join(["%s"] * len(row))
    if update_cols is None:
        update_cols = list(row.keys())
    update_clause = ", ".join([f"{c}=VALUES({c})" for c in update_cols])
    sql = f"INSERT INTO {table} ({cols}) VALUES ({ph}) ON DUPLICATE KEY UPDATE {update_clause}"
    cur.execute(sql, tuple(row.values()))


def insert_pokemon_bundle(cur, p_row: Dict, m_rows: List[Dict]):
    upsert(cur, "pokemon", p_row)   # 포켓몬 마스터 업서트
    for m in m_rows:
        upsert(cur, "move", {"id": m["id"], "name": m["name"], "power": m["power"]})
        # 관계 테이블: (pokemon_id, slot) PK 이므로 REPLACE 사용해도 FK 충돌 없음
        cur.execute(
            """REPLACE INTO pokemon_move (pokemon_id, move_id, slot)
               VALUES (%s, %s, %s)""",
            (p_row["id"], m["id"], m["slot"])
        )


# ─────────────────── 3. Main ETL ───────────────────
def main():
    conn = pymysql.connect(**DB)
    cur  = conn.cursor()
    try:
        for name in tqdm(POKEMONS, desc="ETL"):
            res = fetch_pokemon(name)
            if not res:
                continue
            p_row, m_rows = res
            insert_pokemon_bundle(cur, p_row, m_rows)
            logging.info("upsert %-10s (%d moves)", name, len(m_rows))
        conn.commit()
        logging.info("커밋 완료")
    except Exception as e:
        conn.rollback()
        logging.exception("롤백! : %s", e)
    finally:
        cur.close()
        conn.close()


if __name__ == "__main__":
    main()
