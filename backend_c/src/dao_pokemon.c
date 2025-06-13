#include "dao_pokemon.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define Q_LOAD_SHOP \
 "SELECT id, name, price, image_url FROM pokemon WHERE price IS NOT NULL ORDER BY price"
#define Q_LOAD_MOVES \
 "SELECT m.id, m.name, m.power, m.pp  \
    FROM move m JOIN pokemon_move pm ON pm.move_id = m.id \
   WHERE pm.pokemon_id = %d"

static void die_query(MYSQL* conn, const char* tag) {
    fprintf(stderr, "[%s] %s\n", tag, mysql_error(conn));
}

int load_shop_pokemon(MYSQL* conn, ShopPokemon** outList, int* count) {
    if (mysql_query(conn, Q_LOAD_SHOP)) {
        die_query(conn, "load_shop_pokemon");
        return -1;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    int rows = (int)mysql_num_rows(res);
    ShopPokemon* arr = calloc(rows, sizeof(ShopPokemon));

    for (int i = 0; i < rows; ++i) {
        MYSQL_ROW r = mysql_fetch_row(res);
        arr[i].id = atoi(r[0]);
        strncpy(arr[i].name, r[1], sizeof(arr[i].name) - 1);
        arr[i].price = atoi(r[2]);
        strncpy(arr[i].image_url, r[3], sizeof(arr[i].image_url) - 1);
    }
    mysql_free_result(res);
    *outList = arr; *count = rows;
    return 0;
}

int load_moves_for_pokemon(MYSQL* conn, int pokeId, Move** outList, int* count) {
    char q[256]; snprintf(q, sizeof(q), Q_LOAD_MOVES, pokeId);
    if (mysql_query(conn, q)) { die_query(conn, "load_moves_for_pokemon"); return -1; }
    MYSQL_RES* res = mysql_store_result(conn);
    int rows = (int)mysql_num_rows(res);
    Move* arr = calloc(rows, sizeof(Move));

    for (int i = 0; i < rows; ++i) {
        MYSQL_ROW r = mysql_fetch_row(res);
        arr[i].id = atoi(r[0]);
        strncpy(arr[i].name, r[1], sizeof(arr[i].name) - 1);
        arr[i].power = atoi(r[2]);
        arr[i].pp = atoi(r[3]);
    }
    mysql_free_result(res);
    *outList = arr; *count = rows;
    return 0;
}

void free_shop_pokemon(ShopPokemon* l) { free(l); }
void free_moves(Move* l) { free(l); }
