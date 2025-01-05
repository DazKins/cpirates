#ifndef ENTITY_RENDERER_PLAYER_SHIP_H
#define ENTITY_RENDERER_PLAYER_SHIP_H

#include "render/game/entity/entity_renderer.h"
#include "render/render_context.h"

typedef struct {
  EntityRenderer base;

  Model *model;
} EntityRendererPlayerShip;

EntityRendererPlayerShip EntityRendererPlayerShip_new(Entity *entity);

#endif // !ENTITY_RENDERER_PLAYER_SHIP_H
