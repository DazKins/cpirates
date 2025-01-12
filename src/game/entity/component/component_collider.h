#ifndef COMPONENT_COLLIDER_H
#define COMPONENT_COLLIDER_H

#include "game/entity/component/component.h"
#include "game/entity/component/component_position.h"
#include "math/aabb.h"

typedef struct {
  Component base;

  ComponentPosition *_component_position;

  AABB aabb;
} ComponentColider;

ComponentColider *
ComponentColider_new_ptr(ComponentPosition *component_position, AABB aabb);

#endif // !COMPONENT_COLLIDER_H