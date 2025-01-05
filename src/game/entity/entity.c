#include "entity.h"

#include <stdio.h>
#include <stdlib.h>

Entity Entity_new(EntityType type) {
  Entity entity = {};
  entity.components = List_new();
  entity.type = type;
  entity.id = Id_new();
  return entity;
}

Entity *Entity_new_ptr(EntityType type) {
  Entity *entity = malloc(sizeof(Entity));
  *entity = Entity_new(type);
  return entity;
}

void Entity_tick(Entity *entity) {
  Iterator components_iter = Iterator_new(&entity->components);
  while (Iterator_has_next(&components_iter)) {
    Component *component = Iterator_next(&components_iter);
    Component_tick(component);
  }
}

void Entity_add_component(Entity *entity, Component *component) {
  List_push(&entity->components, component);
}

Component *Entity_get_component(Entity *entity, ComponentType component_type) {
  Iterator components_iter = Iterator_new(&entity->components);
  while (Iterator_has_next(&components_iter)) {
    Component *component = Iterator_next(&components_iter);
    if (component->type == component_type) {
      return component;
    }
  }
  return NULL;
}
