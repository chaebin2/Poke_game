
#include "db.h"
#include <stdio.h>
#include <mysql.h> 

static MYSQL* conn = NULL;

MYSQL* connectDB(void)
{
    conn = mysql_init(NULL);
    if (!conn) { fprintf(stderr, "mysql_init 실패\n"); return NULL; }

    mysql_options(conn, MYSQL_READ_DEFAULT_FILE, "no-ssl.cnf");

    /*  ❗️ 6.x 구버전 대응 : 문자열 “DISABLED” 대신 0 */
    unsigned int ssl_mode = 0;              /* 0 = SSL DISABLED */
    mysql_optionsv(conn, MYSQL_OPT_SSL_MODE, &ssl_mode);

    /* 또는 연결 플래그에서 SSL 요구를 지워버리기 */
    unsigned long flags = 0;                /* CLIENT_FLAGS */
    if (!mysql_real_connect(conn,
        "localhost", "root", "1234",
        "poke_game", 3306, NULL, flags)) {
        fprintf(stderr, "mysql_real_connect 실패: %s\n", mysql_error(conn));
        return NULL;
    }
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
