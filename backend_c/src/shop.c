#include "shop.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pokemon* shopPokemon[SHOP_POKEMON_COUNT];


void initShopPokemon() {
    // ���� ������ (���߿� DB �������� ��ü ����)
    for (int i = 0; i < SHOP_POKEMON_COUNT; i++) {
        shopPokemon[i] = malloc(sizeof(Pokemon));
        shopPokemon[i]->id = i + 1;
        snprintf(shopPokemon[i]->name, sizeof(shopPokemon[i]->name), "poke%d", i + 1);
        shopPokemon[i]->hp = 50 + i * 2;
        shopPokemon[i]->attack = 10 + i;
        shopPokemon[i]->defense = 5 + i;
        shopPokemon[i]->speed = 10 + i;
    }
}

void openShopJson() {
    printf("{\"shop\":[");
    for (int i = 0; i < SHOP_POKEMON_COUNT; i++) {
        printf("{\"id\":%d,\"name\":\"%s\",\"price\":1000}",
            shopPokemon[i]->id, shopPokemon[i]->name);
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