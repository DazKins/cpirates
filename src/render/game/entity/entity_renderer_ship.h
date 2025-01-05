#ifndef ENTITY_SHIP_RENDER_H
#define ENTITY_SHIP_RENDER_H

#include "render/game/entity/entity_renderer.h"
#include "render/render_context.h"

typedef struct {
  EntityRenderer base;

  Model *model;
} EntityRendererShip;

EntityRendererShip EntityRendererShip_new(Entity *entity);

#endif // !ENTITY_SHIP_RENDER_H
