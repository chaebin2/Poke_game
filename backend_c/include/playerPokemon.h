#pragma once

#include "Pokemon.h"
// #include "Skill.h"

typedef struct PlayerPokemon {
    Pokemon* base;               // ���ϸ� ���� ����
    int level;
    int current_hp;
    int is_active;
    // Skill* skills[4];           // ��� 4��
} PlayerPokemon;