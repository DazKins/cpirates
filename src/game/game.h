#ifndef GAME_H
#define GAME_H

#include "game/entity/entity.h"
#include "render/camera.h"
#include "util/list.h"
#include "util/id.h"

int Game_init();
void Game_tick();

void Game_add_entity(Entity *entity);
List Game_get_entities();

void Game_mark_entity_for_deletion(Id entity_id);

extern Camera Game_camera;

#endif // !GAME_H
