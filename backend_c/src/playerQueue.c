
#include "playerQueue.h"
#include "playerPokemon.h"

PlayerPokemonQueue* createPlayerQueue() {
    PlayerPokemonQueue* q = (PlayerPokemonQueue*)malloc(sizeof(PlayerPokemonQueue));
    if (!q) return NULL;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isPlayerQueueEmpty(PlayerPokemonQueue* q) {
    return q->front == NULL;
}

void enqueuePlayer(PlayerPokemonQueue* q, PlayerPokemon* p) {

    PNode* newNode = (PNode*)malloc(sizeof(PNode));
    if (!newNode) return;
    newNode->data = p;
    newNode->link = NULL;
    if (q->rear) {
        q->rear->link = newNode;
    }
    else {
        q->front = newNode;
        q->rear = newNode;
    }
}

PlayerPokemon* dequeuePlayer(PlayerPokemonQueue* q) {
    if (isPlayerQueueEmpty(q)) return NULL;
    PNode* temp = q->front;
    PlayerPokemon* data = temp->data;
    q->front = temp->link;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return data;
}

void freePlayerQueue(PlayerPokemonQueue* q) {
    while (!isPlayerQueueEmpty(q)) {
        dequeuePlayer(q);
    }
    free(q);
}