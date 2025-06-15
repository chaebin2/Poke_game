#include <stdio.h>
#include "battle.h"
#include "Player.h"
#include "dao_pokemon.h"
#include "dao_player.h"
#include "db.h"

/*int main() {
    connectDB();

    Player player = { .pokemon_count = 1, .money = 1000 };
    Pokemon* base = getPokemonById(25); // 피카츄
    PlayerPokemon* p1 = malloc(sizeof(PlayerPokemon));
    p1->base = base;
    p1->level = 5;
    p1->current_hp = base->hp;
    player.pokemon[0] = p1;

    Pokemon* wild = getPokemonById(1); // 이상해씨
    PlayerPokemon* enemy = createEnemy(wild);

    startBattle(&player, enemy);

    disconnectDB();
    return 0;
}
*/

#include "Pokemon.h"
#include "shop.h"

int main() {
    // 1. 플레이어 생성
    Player player = { .pokemon_count = 0, .money = 2000 };  // 2000 포인트로 시작

    // 2. 상점 초기화 (샘플 포켓몬 로딩)
    initShopPokemon();

    // 3. 상점 출력 (JSON 포맷)
    openShopJson();

    // 4. 포켓몬 구매 시도
    buyPokemon(&player, 3);  // ID 3번 포켓몬 구매

    // 5. 다시 구매 시도 (돈 부족 or 중복 확인용)
    buyPokemon(&player, 100);  // 존재하지 않는 포켓몬
    buyPokemon(&player, 2);    // 정상 구매

    // 6. 잔여 금액 및 보유 포켓몬 출력
    printf("남은 돈: %d\n", player.money);
    printf("보유 포켓몬:\n");
    for (int i = 0; i < player.pokemon_count; i++) {
        printf("- %s (Lv.%d)\n", player.pokemon[i]->base->name, player.pokemon[i]->level);
    }

    return 0;
}

