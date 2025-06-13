#ifndef DAO_PLAYER_H
#define DAO_PLAYER_H

#include <mysql.h>

typedef struct {
    int id;          /* player_pokemon PK */
    int base_id;     /* pokemon.id */
    char name[32];
    int level;
    int current_hp;
    int max_hp;
} PlayerPokemon;

int insert_player_pokemon(MYSQL* conn, int playerId, int pokeId);
int load_player_inventory(MYSQL* conn, int playerId, PlayerPokemon** outList, int* count);
void free_player_inventory(PlayerPokemon* list);

#endif
