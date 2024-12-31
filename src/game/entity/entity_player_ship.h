#ifndef ENTITY_PLAYER_SHIP_H
#define ENTITY_PLAYER_SHIP_H

#include "game/entity/entity.h"

typedef struct {
  Entity base;
} EntityPlayerShip;

EntityPlayerShip EntityPlayerShip_new();

#endif // !ENTITY_PLAYER_SHIP_H
