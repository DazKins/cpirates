#ifndef ENTITY_RENDERER_PLAYER_SHIP_H
#define ENTITY_RENDERER_PLAYER_SHIP_H

#include "render/game/entity/entity_renderer.h"
#include "game/entity/entity_player_ship.h"
#include "render/render_context.h"

typedef struct {
  EntityRenderer base;

  Model *model;
} EntityRendererPlayerShip;

EntityRendererPlayerShip EntityRendererPlayerShip_new(EntityPlayerShip *entity_player_ship);

#endif // !ENTITY_RENDERER_PLAYER_SHIP_H
