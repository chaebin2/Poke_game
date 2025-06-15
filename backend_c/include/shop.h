#pragma once

#include "Player.h"      // Player ����ü ���
#include "Pokemon.h"     // Pokemon ����ü ���
#include <stdbool.h>

// ������ ���ϸ� ����Ʈ
#define SHOP_POKEMON_COUNT 10

extern Pokemon* shopPokemon[SHOP_POKEMON_COUNT];

// ���� �ʱ�ȭ (DB���� �ҷ����� ��� ���� ����)
void initShopPokemon();

// JSON �������� ���� ���
void openShopJson();

// ���ϸ� ���� (���� �� true ��ȯ, ���� �� false)
bool buyPokemon(Player* player, int pokemon_id);