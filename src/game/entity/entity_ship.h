#ifndef ENTITY_SHIP_H
#define ENTITY_SHIP_H

#include "entity.h"

typedef struct {
  Entity base;
} EntityShip;

EntityShip EntityShip_new();

#endif // !ENTITY_SHIP_H
