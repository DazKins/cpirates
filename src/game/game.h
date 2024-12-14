#ifndef GAME_H
#define GAME_H

#include "render/camera.h"
#include "util/list.h"

int Game_init();
void Game_tick();

extern List Game_entities;
extern Camera Game_camera;

#endif // !GAME_H
