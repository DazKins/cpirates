#ifndef ENTITY_H
#define ENTITY_H

#include "math/v.h"
#include "util/id.h"

typedef enum {
  EntityTypeShip,
  EntityTypePlayerShip,
} EntityType;

typedef struct _entity {
  Id id;
  EntityType type;
  V pos;
  V vel;

  void (*_tickFunc)(struct _entity *entity);
} Entity;

void Entity_tick(Entity *entity);

#endif // !ENTITY_H
