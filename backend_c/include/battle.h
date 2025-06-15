#pragma once

#include "Pokemon.h"
#include "PlayerPokemon.h"
#include "Player.h"

PlayerPokemon* createEnemy(Pokemon* base);
int calculateDamage(PlayerPokemon* attacker, PlayerPokemon* defender);
int startBattle(Player* player, PlayerPokemon* enemy);

