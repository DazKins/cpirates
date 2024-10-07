#ifndef ENTITY_H
#define ENTITY_H

#include "../../math/v.h"

typedef enum {
  EntityTypeShip,
} EntityType;

typedef struct {
  EntityType type;
  V pos;
} Entity;

#endif // !ENTITY_H
