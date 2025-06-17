#pragma once

#define MAX_URL_LEN 256
#define MAX_POKEMON 100

typedef struct {
	int id;
	char name[30];
	int hp, attack, defense, speed;
	char image_url[MAX_URL_LEN];
} Pokemon;

extern Pokemon pokemonList[MAX_POKEMON]; // ��ü ���ϸ� �迭
extern int pokemonCount;