#pragma once

#include <mysql.h>
#include "Pokemon.h"

MYSQL* connectDB();
Pokemon* getPokemonById(int id);
void disconnectDB();