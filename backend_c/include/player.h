#pragma once

#include "PlayerPokemon.h"

typedef struct Player {
    PlayerPokemon* pokemon[6];  // ���� ���ϸ� �ִ� 6����
    int pokemon_count;          // ���� ���� ��
    int money;                  // ���� ��� ���
} Player;