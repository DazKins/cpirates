#include "component_collider.h"

#include <stdlib.h>

ComponentCollider *
ComponentCollider_new_ptr(ComponentPosition *component_position,
                          void (*on_collide_func)(Entity *entity), AABB aabb) {
  ComponentCollider *component_collider = malloc(sizeof(ComponentCollider));

  component_collider->base = Component_new(ComponentTypeCollider, NULL);

  component_collider->_component_position = component_position;
  component_collider->_on_collide_func = on_collide_func;
  component_collider->_aabb = aabb;

  return component_collider;
}

AABB ComponentCollider_get_aabb(ComponentCollider *component_collider) {
  ComponentPosition *component_position =
      component_collider->_component_position;

  AABB aabb = component_collider->_aabb;

  return AABB_translate(aabb, component_position->pos);
}

void ComponentCollider_on_collide(ComponentCollider *component_collider,
                                  Entity *entity) {
  component_collider->_on_collide_func(entity);
}