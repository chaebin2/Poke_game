#include "dao_player.h"
#include "playerPokemon.h"
#include "player.h"
#include "shop.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "db.h"

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

        arr[i].base->id = atoi(row[1]);  // player_pokemon.id�� row[0], base id�� row[1]
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
        free(l[i].base);  // ���� �����͵� ����
    free(l);
}



// ����
void savePlayerState(Player* player) {
    MYSQL* conn = connectDB();
    if (!conn) {
        fprintf(stderr, "[savePlayerState] DB ���� ����\n");
        return;
    }

    const char* deleteQuery = "DELETE FROM player_pokemon WHERE player_id = 1";
    if (mysql_query(conn, deleteQuery)) {
        fprintf(stderr, "[savePlayerState] ���� ����: %s\n", mysql_error(conn));
        disconnectDB();
        return;
    }

    for (int i = 0; i < player->pokemon_count; i++) {
        PlayerPokemon* pp = player->pokemon[i];
        int pokemon_id = pp->base->id;
        int current_hp = pp->current_hp;
        int is_active = pp->is_active;

        char insertQuery[256];
        snprintf(insertQuery, sizeof(insertQuery),
            "INSERT INTO player_pokemon (player_id, pokemon_id, current_hp, is_active) "
            "VALUES (1, %d, %d, %d)",
            pokemon_id, current_hp, is_active
        );

        if (mysql_query(conn, insertQuery)) {
            fprintf(stderr, "[savePlayerState] ���� ����: %s\n", mysql_error(conn));
        }
    }

    disconnectDB();
}


// �ҷ�����
void loadPlayerState(Player* player) {
    MYSQL* conn = connectDB();
    if (!conn) {
        fprintf(stderr, "[loadPlayerState] DB ���� ����\n");
        return;
    }

    const char* query = "SELECT pokemon_id, current_hp, is_active FROM player_pokemon WHERE player_id = 1";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "[loadPlayerState] ���� ����: %s\n", mysql_error(conn));
        disconnectDB();
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    int idx = 0;
    while ((row = mysql_fetch_row(res)) && idx < MAX_PLAYER_POKEMON) {
        int pokemon_id = atoi(row[0]);
        int current_hp = atoi(row[1]);
        int is_active = atoi(row[2]);

        PlayerPokemon* pp = (PlayerPokemon*)malloc(sizeof(PlayerPokemon));
        memset(pp, 0, sizeof(PlayerPokemon));
        pp->base = getPokemonById(pokemon_id);
        if (!pp->base) {
            fprintf(stderr, "[loadPlayerState] ���ϸ� �ε� ����: id %d\n", pokemon_id);
            free(pp);
            continue;
        }

        pp->current_hp = current_hp;
        pp->is_active = is_active;

        player->pokemon[idx++] = pp;
    }

    player->pokemon_count = idx;

    // �ӽ�: ���� ���� player ���̺��� �ε� ����
    player->money = 5000;

    mysql_free_result(res);
    disconnectDB();
}

