#include "dao_player.h"
#include "playerPokemon.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void die_query(MYSQL* c, const char* tag) { fprintf(stderr, "[%s] %s\n", tag, mysql_error(c)); }

int insert_player_pokemon(MYSQL* c, int pid, int poke) {
    char q[128];
    snprintf(q, sizeof(q),
        "INSERT INTO player_pokemon(player_id,pokemon_id,level) "
        "VALUES(%d,%d,1) ON DUPLICATE KEY UPDATE level=level", pid, poke);
    return mysql_query(c, q) ? (die_query(c, "insert_player_pokemon"), -1) : 0;
}

int load_player_inventory(MYSQL* c, int pid, PlayerPokemon** out, int* cnt) {
    char q[256];
    snprintf(q, sizeof(q),
        "SELECT pp.id,p.id,p.name,pp.level,pp.current_hp,p.hp "
        "FROM player_pokemon pp JOIN pokemon p ON p.id=pp.pokemon_id "
        "WHERE pp.player_id=%d", pid);
    if (mysql_query(c, q)) { die_query(c, "load_player_inventory"); return -1; }
    MYSQL_RES* r = mysql_store_result(c);
    int n = (int)mysql_num_rows(r);
    PlayerPokemon* arr = calloc(n, sizeof(PlayerPokemon));
    for (int i = 0; i < n; ++i) {
        MYSQL_ROW row = mysql_fetch_row(r);
        arr[i].base = malloc(sizeof(Pokemon));

        arr[i].base->id = atoi(row[1]);  // player_pokemon.id는 row[0], base id는 row[1]
        strncpy(arr[i].base->name, row[2], sizeof(arr[i].base->name) - 1);
        arr[i].level = atoi(row[3]);
        arr[i].current_hp = atoi(row[4]);
        arr[i].base->hp = atoi(row[5]);
    }
    mysql_free_result(r);
    *out = arr; *cnt = n; return 0;
}

void free_player_inventory(PlayerPokemon* l, int cnt) {
    for (int i = 0; i < cnt; ++i)
        free(l[i].base);  // 내부 포인터도 해제
    free(l);
}
