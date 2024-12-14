#ifndef ENTITY_SHIP_RENDER_H
#define ENTITY_SHIP_RENDER_H

#include "render/game/entity/entity.h"
#include "game/entity/entity_ship.h"
#include "render/render_context.h"

typedef struct {
  EntityRenderer base;

  Model *model;
} EntityRendererShip;

EntityRendererShip EntityRendererShip_new(EntityShip *entity_ship);

void EntityRendererShip_render(EntityRendererShip *entity_renderer_ship, RenderContext *render_context);

#endif // !ENTITY_SHIP_RENDER_H
