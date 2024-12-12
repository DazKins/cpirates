#ifndef ENTITY_SHIP_RENDER_H
#define ENTITY_SHIP_RENDER_H

#include "render/game/entity/entity.h"
#include "game/entity/entity_ship.h"

typedef struct {
  EntityRenderer base;
} EntityRendererShip;

EntityRendererShip EntityRendererShip_new(EntityShip *entity_ship);

#endif // !ENTITY_SHIP_RENDER_H
