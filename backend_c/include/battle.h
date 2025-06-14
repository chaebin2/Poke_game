#pragma once

#include "Pokemon.h"
#include "PlayerPokemon.h"
#include "Player.h"

PlayerPokemon* createEnemy(Pokemon* base);
void startBattle(Player* player, PlayerPokemon* enemy);
