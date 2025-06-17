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
        initShopPokemon();  // createEnemy 내부에서 포인터 참조하니까 필요
        Player player;
        loadPlayerState(&player);

        if (player.pokemon_count == 0) {
            printf("{\"result\": \"no_pokemon\"}\n");
            return 0;
        }

        // 적 포켓몬 임시로 0번 포켓몬으로 고정
        Pokemon* enemyBase = shopPokemon[0];  // 추후 라운드별 난이도에 따라 변경 가능
        PlayerPokemon* enemy = createEnemy(enemyBase);

        int win = startBattle(&player, enemy);

        if (win) {
            player.money += 1000;  // 보상
            printf("{\"event\":\"reward\",\"money\":%d}\n", player.money);
        }
        else {
            // 패배 시 별도 처리 없음 (추후 회복/패널티 추가 가능)
        }

        savePlayerState(&player);
        free(enemy);
        return 0;
    }
}