#pragma once

int connectDB(void);
void disconnectDB(void);
int loadPokemon(Pokemon* list, int* count);
