#pragma once

#include "Pokemon.h"
// #include "Skill.h"

typedef struct PlayerPokemon {
    Pokemon* base;               // ���ϸ� ���� ����
    int level;
    int current_hp;
    // Skill* skills[4];           // ��� 4��
} PlayerPokemon;