#pragma once

#include "Pokemon.h"
#include <stdlib.h>
#include <stdio.h>

struct PlayerPokemon;
typedef struct PlayerPokemon PlayerPokemon;

// ������ ����� PlayerPokemon ��� ť ���
typedef struct PNode {
    PlayerPokemon* data;
    struct PNode* link;
} PNode;

// ť ����ü ����
typedef struct {
    PNode* front;
    PNode* rear;
} PlayerPokemonQueue;

PlayerPokemonQueue* createPlayerQueue();
int isPlayerQueueEmpty(PlayerPokemonQueue* q);
void enqueuePlayer(PlayerPokemonQueue* q, PlayerPokemon* p);
PlayerPokemon* dequeuePlayer(PlayerPokemonQueue* q);
void freePlayerQueue(PlayerPokemonQueue* q);
