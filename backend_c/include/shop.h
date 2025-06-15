#pragma once

#include "Player.h"      // Player 구조체 사용
#include "Pokemon.h"     // Pokemon 구조체 사용
#include <stdbool.h>

// 상점용 포켓몬 리스트
#define SHOP_POKEMON_COUNT 10

extern Pokemon* shopPokemon[SHOP_POKEMON_COUNT];

// 상점 초기화 (DB에서 불러오는 대신 샘플 세팅)
void initShopPokemon();

// JSON 형식으로 상점 출력
void openShopJson();

// 포켓몬 구매 (성공 시 true 반환, 실패 시 false)
bool buyPokemon(Player* player, int pokemon_id);