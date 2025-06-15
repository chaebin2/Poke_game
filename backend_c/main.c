    #include <stdio.h>
    #include "battle.h"
    #include "player.h"
    #include "dao_pokemon.h"
    #include "dao_player.h"
    #include "db.h"
    #include "Pokemon.h"
    #include "shop.h"

    #include <string.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <io.h>

    int main(int argc, char* argv[]) {
        _setmode(_fileno(stdout), _O_BINARY);
        setvbuf(stdout, NULL, _IONBF, 0);

        if (argc > 1 && strcmp(argv[1], "shop") == 0) {
            initShopPokemon();
            openShopJson();
            fflush(stdout);
            exit(0);
        }
        else if (strcmp(argv[1], "buy") == 0 && argc == 3) {
            int id = atoi(argv[2]);

            initShopPokemon();
            Player player;

            loadPlayerState(&player);
            buyPokemon(&player, id); // 기존 함수 그대로 사용
            savePlayerState(&player);
            return 0;
        }
        else if (strcmp(argv[1], "mypokemon") == 0) {
            initShopPokemon(); // 반드시 있어야 shopPokemon[i]->id 등 복구 가능
            Player player;
            loadPlayerState(&player);
            showMyPokemonJson(&player);
            return 0;
        }
        else if (strcmp(argv[1], "money") == 0) {
            initShopPokemon();
            Player player;
            loadPlayerState(&player);
            printf("{\"money\": %d}\n", player.money);
            return 0;
        }

        else if (strcmp(argv[1], "battle") == 0) {
            initShopPokemon();
            Player player;
            loadPlayerState(&player);

            if (player.pokemon_count == 0) {
                printf("{\"error\": \"No Pokemon\"}\n");
                return 0;
            }

            PlayerPokemon* myPoke = player.pokemon[0];

            Pokemon enemy = { 999, "EnemyMon", 100, 40, 40, 50 }; // 예시 적
            char* result = myPoke->base->speed >= enemy.speed ? "win" : "lose";

            printf("{\"battle_result\": \"%s\", \"player_speed\": %d, \"enemy_speed\": %d}\n",
                result, myPoke->base->speed, enemy.speed);
            return 0;
        }

        return 0;
    }