#include "shop.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "db.h"
#include "pokemon.h"

int pokemonCount = 0;

Pokemon* shopPokemon[SHOP_POKEMON_COUNT];



void initShopPokemon() {
    MYSQL* conn = connectDB();
    if (!conn) {
        fprintf(stderr, "[initShopPokemon] DB ���� ����\n");
        return;
    }

    const char* query = "SELECT id, name, hp, attack, defense, speed, image_url FROM pokemon LIMIT 10";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "[initShopPokemon] ���� ����: %s\n", mysql_error(conn));
        disconnectDB();
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    int i = 0;
    while ((row = mysql_fetch_row(res)) && i < SHOP_POKEMON_COUNT) {
        Pokemon* p = malloc(sizeof(Pokemon));
        p->id = atoi(row[0]);
        strncpy(p->name, row[1], sizeof(p->name) - 1);
        p->hp = atoi(row[2]);
        p->attack = atoi(row[3]);
        p->defense = atoi(row[4]);
        p->speed = atoi(row[5]);
        strncpy(p->image_url, row[6], sizeof(p->image_url) - 1);

        shopPokemon[i++] = p;
    }

    pokemonCount = i;

    mysql_free_result(res);
    disconnectDB();
}

void openShopJson() {
    printf("{\"shop\":[");
    for (int i = 0; i < SHOP_POKEMON_COUNT; i++) {
        printf("{\"id\":%d,\"name\":\"%s\",\"price\":1000,\"image_url\":\"%s\"}",
            shopPokemon[i]->id, shopPokemon[i]->name, shopPokemon[i]->image_url);
        if (i < SHOP_POKEMON_COUNT - 1) printf(",");
    }
    printf("]}\n");
}

bool buyPokemon(Player* player, int pokemon_id) {
    // �⺻ ���� ���� (���� ���� �����ϴٰ� ����)
    const int price = 1000;

    // �� Ȯ��
    if (player->money < price) {
        printf("{\"success\": false, \"error\": \"Not enough money\"}\n");
        return false;
    }

    // ���ϸ� ã��
    for (int i = 0; i < SHOP_POKEMON_COUNT; i++) {
        if (shopPokemon[i]->id == pokemon_id) {
            PlayerPokemon* newPoke = malloc(sizeof(PlayerPokemon));
            memset(newPoke, 0, sizeof(PlayerPokemon));

            newPoke->base = shopPokemon[i];
            newPoke->level = 1;
            newPoke->current_hp = shopPokemon[i]->hp;

            player->pokemon[player->pokemon_count++] = newPoke;
            player->money -= price;

            printf("{\"success\": true, \"pokemon\": {\"id\": %d, \"name\": \"%s\", \"price\": %d}}\n",
                shopPokemon[i]->id, shopPokemon[i]->name, price);
            return true;
        }
    }

    printf("{\"success\": false, \"error\": \"Invalid Pokemon ID\"}\n");
    return false;
}