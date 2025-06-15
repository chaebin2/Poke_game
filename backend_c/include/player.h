#pragma once

#include "PlayerPokemon.h"

#define MAX_PLAYER_POKEMON 6

typedef struct Player {
    PlayerPokemon* pokemon[6];  // ���� ���ϸ� �ִ� 6����
    int pokemon_count;          // ���� ���� ��
    int money;                  // ���� ��� ���
} Player;