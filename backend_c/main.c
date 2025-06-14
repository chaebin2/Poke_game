#include <stdio.h>
#include "battle.h"
#include "Player.h"
#include "dao_pokemon.h"
#include "dao_player.h"
#include "db.h"

int main() {
    connectDB();

    Player player = { .pokemon_count = 1, .money = 1000 };
    Pokemon* base = getPokemonById(25); // ÇÇÄ«Ãò
    PlayerPokemon* p1 = malloc(sizeof(PlayerPokemon));
    p1->base = base;
    p1->level = 5;
    p1->current_hp = base->hp;
    player.pokemon[0] = p1;

    Pokemon* wild = getPokemonById(1); // ÀÌ»óÇØ¾¾
    PlayerPokemon* enemy = createEnemy(wild);

    startBattle(&player, enemy);

    disconnectDB();
    return 0;
}
