#include "component_collider.h"

#include <stdlib.h>

ComponentColider *
ComponentColider_new_ptr(ComponentPosition *component_position, AABB aabb) {
  ComponentColider *component_colider = malloc(sizeof(ComponentColider));

  component_colider->base = Component_new(ComponentTypeCollider, NULL);

  component_colider->_component_position = component_position;
  component_colider->aabb = aabb;

  return component_colider;
}