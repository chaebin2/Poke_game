#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"
#include "playerQueue.h"

// 적 포켓몬 생성 (랜덤 레벨 5~9)
PlayerPokemon* createEnemy(Pokemon* base) {
    PlayerPokemon* enemy = (PlayerPokemon*)malloc(sizeof(PlayerPokemon));
    enemy->base = base;
    enemy->level = 5 + rand() % 5;
    enemy->current_hp = base->hp*2;
    return enemy;
}

// 데미지 계산 (기본 공식)
int calculateDamage(PlayerPokemon* attacker, PlayerPokemon* defender) {
    int damage = attacker->base->attack - defender->base->defense;
    if (damage < 1) damage = 1;
    return damage;
}

int startBattle(Player* player, PlayerPokemon* enemy) {
    srand((unsigned int)time(NULL));

    PlayerPokemonQueue* queue = createPlayerQueue();
    for (int i = 0; i < player->pokemon_count; i++) {
        if (player->pokemon[i] && player->pokemon[i]->current_hp > 0) {
            enqueuePlayer(queue, player->pokemon[i]);
        }
    }

    PlayerPokemon* myPoke = dequeuePlayer(queue);
    if (!myPoke) {
        printf("{\"result\":\"no_pokemon\"}\n");
        freePlayerQueue(queue);
        return 0;
    }

    printf("{\"event\":\"battle_start\",\"enemy\":\"%s\"}\n", enemy->base->name);

    while (1) {
        printf("{\"event\":\"turn\",\"my\":\"%s\",\"my_hp\":%d,\"enemy\":\"%s\",\"enemy_hp\":%d}\n",
            myPoke->base->name, myPoke->current_hp,
            enemy->base->name, enemy->current_hp);

        int myFirst = myPoke->base->speed >= enemy->base->speed;

        if (myFirst) {
            int dmg = calculateDamage(myPoke, enemy);
            enemy->current_hp -= dmg;
            if (enemy->current_hp < 0) enemy->current_hp = 0;

            printf("{\"event\":\"attack\",\"attacker\":\"%s\",\"damage\":%d}\n",
                myPoke->base->name, dmg);

            if (enemy->current_hp <= 0) {
                printf("{\"result\":\"win\",\"enemy\":\"%s\"}\n", enemy->base->name);
                freePlayerQueue(queue);
                return 1;  // 승리
            }

            dmg = calculateDamage(enemy, myPoke);
            myPoke->current_hp -= dmg;
            if (myPoke->current_hp < 0) myPoke->current_hp = 0;

            printf("{\"event\":\"attack\",\"attacker\":\"%s\",\"damage\":%d}\n",
                enemy->base->name, dmg);
        }
        else {
            int dmg = calculateDamage(enemy, myPoke);
            myPoke->current_hp -= dmg;
            if (myPoke->current_hp < 0) myPoke->current_hp = 0;

            printf("{\"event\":\"attack\",\"attacker\":\"%s\",\"damage\":%d}\n",
                enemy->base->name, dmg);

            if (myPoke->current_hp <= 0) {
                printf("{\"event\":\"fainted\",\"pokemon\":\"%s\"}\n", myPoke->base->name);
                myPoke = dequeuePlayer(queue);
                if (!myPoke) {
                    printf("{\"result\":\"lose\"}\n");
                    freePlayerQueue(queue);
                    return 0;  // 패배
                }
                printf("{\"event\":\"send_next\",\"pokemon\":\"%s\"}\n", myPoke->base->name);
                continue;
            }

            dmg = calculateDamage(myPoke, enemy);
            enemy->current_hp -= dmg;
            if (enemy->current_hp < 0) enemy->current_hp = 0;

            printf("{\"event\":\"attack\",\"attacker\":\"%s\",\"damage\":%d}\n",
                myPoke->base->name, dmg);

            if (enemy->current_hp <= 0) {
                printf("{\"result\":\"win\",\"enemy\":\"%s\"}\n", enemy->base->name);
                freePlayerQueue(queue);
                return 1;  // 승리
            }
        }

        if (myPoke->current_hp <= 0) {
            printf("{\"event\":\"fainted\",\"pokemon\":\"%s\"}\n", myPoke->base->name);
            myPoke = dequeuePlayer(queue);
            if (!myPoke) {
                printf("{\"result\":\"lose\"}\n");
                freePlayerQueue(queue);
                return 0;  // 패배
            }
            printf("{\"event\":\"send_next\",\"pokemon\":\"%s\"}\n", myPoke->base->name);
        }
    }
}
