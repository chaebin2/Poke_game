#include <stdio.h>
#include "player.h"

void showMyPokemonJson(Player* player) {
    printf("{\"mypokemon\":[");

    for (int i = 0; i < player->pokemon_count; i++) {
        PlayerPokemon* pp = player->pokemon[i];
        printf("{\"id\":%d,\"name\":\"%s\",\"level\":%d,\"current_hp\":%d}",
            pp->base->id, pp->base->name, pp->level, pp->current_hp);
        if (i < player->pokemon_count - 1) printf(",");
    }

    printf("]}\n");
}
