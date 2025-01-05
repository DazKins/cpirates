#ifndef ENTITY_H
#define ENTITY_H

#include "math/v.h"
#include "util/id.h"
#include "util/list.h"
#include "component/component.h"

typedef enum {
  EntityTypeShip,
  EntityTypePlayerShip,
} EntityType;

typedef struct _entity {
  Id id;
  EntityType type;
  List components;
} Entity;

Entity Entity_new(EntityType type);

void Entity_tick(Entity *entity);
void Entity_add_component(Entity *entity, Component *component);
Component *Entity_get_component(Entity *entity, ComponentType component_type);

#endif // !ENTITY_H
