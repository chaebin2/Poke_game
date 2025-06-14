#pragma once

#include "Pokemon.h"
// #include "Skill.h"

typedef struct PlayerPokemon {
    Pokemon* base;               // 포켓몬 도감 정보
    int level;
    int current_hp;
    // Skill* skills[4];           // 기술 4개
} PlayerPokemon;