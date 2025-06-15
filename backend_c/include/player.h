#pragma once

#include "PlayerPokemon.h"

#define MAX_PLAYER_POKEMON 6

typedef struct Player {
    PlayerPokemon* pokemon[6];  // 보유 포켓몬 최대 6마리
    int pokemon_count;          // 현재 보유 수
    int money;                  // 상점 기능 대비
} Player;

void showMyPokemonJson(Player* player);