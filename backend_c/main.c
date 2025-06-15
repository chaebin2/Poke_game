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
        buyPokemon(&player, id); // ���� �Լ� �״�� ���
        savePlayerState(&player);
        return 0;
    }
    else if (strcmp(argv[1], "mypokemon") == 0) {
        initShopPokemon(); // �ݵ�� �־�� shopPokemon[i]->id �� ���� ����
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
        initShopPokemon();  // createEnemy ���ο��� ������ �����ϴϱ� �ʿ�
        Player player;
        loadPlayerState(&player);

        if (player.pokemon_count == 0) {
            printf("{\"result\": \"no_pokemon\"}\n");
            return 0;
        }

        // �� ���ϸ� �ӽ÷� 0�� ���ϸ����� ����
        Pokemon* enemyBase = shopPokemon[0];  // ���� ���庰 ���̵��� ���� ���� ����
        PlayerPokemon* enemy = createEnemy(enemyBase);

        int win = startBattle(&player, enemy);

        if (win) {
            player.money += 1000;  // ����
            printf("{\"event\":\"reward\",\"money\":%d}\n", player.money);
        }
        else {
            // �й� �� ���� ó�� ���� (���� ȸ��/�г�Ƽ �߰� ����)
        }

        savePlayerState(&player);
        free(enemy);
        return 0;
    }
}