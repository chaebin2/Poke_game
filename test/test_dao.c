#include <stdio.h>
#include <mysql.h>
#include "dao_pokemon.h"
#include "dao_player.h"

#define DB_HOST "localhost"
#define DB_PORT 13306
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "poke_game"

int main() {
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0)) {
        fprintf(stderr, "DB 연결 실패: %s\n", mysql_error(conn)); return 1;
    }
    ShopPokemon* shop = NULL; int sc = 0;
    if (!load_shop_pokemon(conn, &shop, &sc)) {
        printf("{\"shop\":[");
        for (int i = 0;i < sc;++i) {
            printf("{\"id\":%d,\"name\":\"%s\",\"price\":%d}", shop[i].id, shop[i].name, shop[i].price);
            if (i < sc - 1)printf(",");
        }
        puts("]}");
        free_shop_pokemon(shop);
    }
    mysql_close(conn); return 0;
}
