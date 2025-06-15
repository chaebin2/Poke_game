#include "shop.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pokemon* shopPokemon[SHOP_POKEMON_COUNT];

void initShopPokemon() {
    // 샘플 데이터 (나중에 DB 연동으로 대체 가능)
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
    if (player->money < 1000) {
        printf("{\"result\":\"fail\",\"reason\":\"not enough money\"}\n");
        return false;
    }

    for (int i = 0; i < SHOP_POKEMON_COUNT; i++) {
        if (shopPokemon[i]->id == pokemon_id) {
            if (player->pokemon_count >= MAX_PLAYER_POKEMON) {
                printf("{\"result\":\"fail\",\"reason\":\"party full\"}\n");
                return false;
            }

            PlayerPokemon* newPoke = malloc(sizeof(PlayerPokemon));
            newPoke->base = shopPokemon[i];
            newPoke->level = 1;
            newPoke->current_hp = shopPokemon[i]->hp;

            player->pokemon[player->pokemon_count++] = newPoke;
            player->money -= 1000;

            printf("{\"result\":\"success\",\"name\":\"%s\"}\n", shopPokemon[i]->name);
            return true;
        }
    }

    printf("{\"result\":\"fail\",\"reason\":\"invalid id\"}\n");
    return false;
}
