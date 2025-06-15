#include <stdio.h>
#include "battle.h"
#include "Player.h"
#include "dao_pokemon.h"
#include "dao_player.h"
#include "db.h"

/*int main() {
    connectDB();

    Player player = { .pokemon_count = 1, .money = 1000 };
    Pokemon* base = getPokemonById(25); // ��ī��
    PlayerPokemon* p1 = malloc(sizeof(PlayerPokemon));
    p1->base = base;
    p1->level = 5;
    p1->current_hp = base->hp;
    player.pokemon[0] = p1;

    Pokemon* wild = getPokemonById(1); // �̻��ؾ�
    PlayerPokemon* enemy = createEnemy(wild);

    startBattle(&player, enemy);

    disconnectDB();
    return 0;
}
*/

#include "Pokemon.h"
#include "shop.h"

int main() {
    // 1. �÷��̾� ����
    Player player = { .pokemon_count = 0, .money = 2000 };  // 2000 ����Ʈ�� ����

    // 2. ���� �ʱ�ȭ (���� ���ϸ� �ε�)
    initShopPokemon();

    // 3. ���� ��� (JSON ����)
    openShopJson();

    // 4. ���ϸ� ���� �õ�
    buyPokemon(&player, 3);  // ID 3�� ���ϸ� ����

    // 5. �ٽ� ���� �õ� (�� ���� or �ߺ� Ȯ�ο�)
    buyPokemon(&player, 100);  // �������� �ʴ� ���ϸ�
    buyPokemon(&player, 2);    // ���� ����

    // 6. �ܿ� �ݾ� �� ���� ���ϸ� ���
    printf("���� ��: %d\n", player.money);
    printf("���� ���ϸ�:\n");
    for (int i = 0; i < player.pokemon_count; i++) {
        printf("- %s (Lv.%d)\n", player.pokemon[i]->base->name, player.pokemon[i]->level);
    }

    return 0;
}

