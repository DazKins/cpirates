#ifndef ENTITY_H
#define ENTITY_H

#include "game/entity/component/component.h"
#include "math/v.h"
#include "util/id.h"
#include "util/list.h"

typedef enum {
  EntityTypeShip,
} EntityType;

typedef struct _entity {
  Id id;
  EntityType type;
  List components;
} Entity;

Entity Entity_new(EntityType type);
Entity *Entity_new_ptr(EntityType type);

void Entity_tick(Entity *entity);
void Entity_add_component(Entity *entity, Component *component);
Component *Entity_get_component(Entity *entity, ComponentType component_type);

#endif // !ENTITY_H
