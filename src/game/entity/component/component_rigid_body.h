#ifndef COMPONENT_RIGID_BODY_H
#define COMPONENT_RIGID_BODY_H

#include "game/entity/component/component.h"
#include "game/entity/component/component_position.h"

typedef struct {
  Component base;

  ComponentPosition *_component_position;
  V velocity;
} ComponentRigidBody;

ComponentRigidBody
ComponentRigidBody_new(ComponentPosition *component_position);

void ComponentRigidBody_push(ComponentRigidBody *component_rigid_body,
                             V push_direction, float push_force);

#endif // !COMPONENT_RIGID_BODY_H