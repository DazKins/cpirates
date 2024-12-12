#ifndef GAME_H
#define GAME_H

#include "util/list.h"

int Game_init();
void Game_tick();

extern List Game_entities;

#endif // !GAME_H
