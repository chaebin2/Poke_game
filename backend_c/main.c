#include <stdio.h>
#include "battle.h"
#include "Player.h"
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

    // 테스트 로직 (FastAPI용 아님)
    return 0;
}