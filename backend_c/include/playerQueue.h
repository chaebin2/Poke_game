#pragma once

#include "Pokemon.h"
#include <stdlib.h>
#include <stdio.h>

struct PlayerPokemon;
typedef struct PlayerPokemon PlayerPokemon;

// 전투에 사용할 PlayerPokemon 기반 큐 노드
typedef struct PNode {
    PlayerPokemon* data;
    struct PNode* link;
} PNode;

// 큐 구조체 정의
typedef struct {
    PNode* front;
    PNode* rear;
} PlayerPokemonQueue;

PlayerPokemonQueue* createPlayerQueue();
int isPlayerQueueEmpty(PlayerPokemonQueue* q);
void enqueuePlayer(PlayerPokemonQueue* q, PlayerPokemon* p);
PlayerPokemon* dequeuePlayer(PlayerPokemonQueue* q);
void freePlayerQueue(PlayerPokemonQueue* q);
