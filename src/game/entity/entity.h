#ifndef ENTITY_H
#define ENTITY_H

#include "math/v.h"
#include "util/id.h"

typedef enum {
  EntityTypeShip,
  EntityTypePlayerShip,
} EntityType;

typedef struct {
  Id id;
  EntityType type;
  V pos;
} Entity;

#endif // !ENTITY_H
