#ifndef DAO_PLAYER_H
#define DAO_PLAYER_H

#include <mysql.h>
#include "playerPokemon.h"
#include "player.h"

// db�� �Լ�
int insert_player_pokemon(MYSQL* conn, int playerId, int pokeId);
int load_player_inventory(MYSQL* conn, int playerId, PlayerPokemon** outList, int* count);
void free_player_inventory(PlayerPokemon* list);

// ���� ����� �Լ�
void savePlayerState(Player* player);
void loadPlayerState(Player* player);

#endif
