#ifndef DAO_POKEMON_H
#define DAO_POKEMON_H

#include <mysql.h>

typedef struct {
    int  id;
    char name[32];
    int  price;
    char image_url[128];
} ShopPokemon;

typedef struct {
    int  id;
    char name[32];
    int  power;
    int  pp;
} Move;

int  load_shop_pokemon(MYSQL* conn, ShopPokemon** outList, int* count);
int  load_moves_for_pokemon(MYSQL* conn, int pokeId, Move** outList, int* count);

void free_shop_pokemon(ShopPokemon* list);
void free_moves(Move* list);

#endif
