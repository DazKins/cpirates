#ifndef ENTITY_PLAYER_SHIP_H
#define ENTITY_PLAYER_SHIP_H

#include "game/entity/entity.h"

typedef struct {
  Entity base;
} EntityPlayerShip;

EntityPlayerShip EntityPlayerShip_new();
void EntityPlayerShip_push(EntityPlayerShip *entity_player_ship, V push_vector,
                           float push_force);

#endif // !ENTITY_PLAYER_SHIP_H
