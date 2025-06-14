
#include "db.h"
#include <stdio.h>

static MYSQL* conn = NULL;

MYSQL* connectDB() {
    conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "1234", "poke_game", 13306, NULL, 0);
    return conn;
}

Pokemon* getPokemonById(int id) {
    if (!conn) return NULL;

    char q[128];
    snprintf(q, sizeof(q), "SELECT id, name, hp, attack, defense, speed FROM pokemon WHERE id=%d", id);

    if (mysql_query(conn, q)) {
        fprintf(stderr, "[getPokemonById] %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_RES* r = mysql_store_result(conn);
    if (mysql_num_rows(r) == 0) {
        mysql_free_result(r);
        return NULL;
    }

    MYSQL_ROW row = mysql_fetch_row(r);
    Pokemon* p = malloc(sizeof(Pokemon));
    p->id = atoi(row[0]);
    strncpy(p->name, row[1], sizeof(p->name) - 1);
    p->hp = atoi(row[2]);
    p->attack = atoi(row[3]);
    p->defense = atoi(row[4]);
    p->speed = atoi(row[5]);

    mysql_free_result(r);
    return p;
}

void disconnectDB() {
    if (conn) {
        mysql_close(conn);
        conn = NULL;
    }
}
