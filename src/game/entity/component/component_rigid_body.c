#include "component_rigid_body.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ComponentRigidBody_tick(Component *component) {
  ComponentRigidBody *component_rigid_body = (ComponentRigidBody *)component;

  component_rigid_body->_component_position->pos =
      V_add(component_rigid_body->_component_position->pos,
            component_rigid_body->velocity);

  float desired_angle = -atan2f(component_rigid_body->velocity.x, component_rigid_body->velocity.z);
  float current_angle = component_rigid_body->_component_position->rot.y;

  float angle_diff = desired_angle - current_angle;

  if (angle_diff > M_PI) {
    angle_diff -= 2.0f * M_PI;
  } else if (angle_diff < -M_PI) {
    angle_diff += 2.0f * M_PI;
  }

  component_rigid_body->_component_position->rot.y = current_angle + angle_diff * 0.05f;

  component_rigid_body->velocity = V_mul(component_rigid_body->velocity, 0.9f);
}

void ComponentRigidBody_push(ComponentRigidBody *component_rigid_body,
                             V push_direction, float push_force) {
  component_rigid_body->velocity =
      V_add(component_rigid_body->velocity, V_mul(push_direction, push_force));
}

ComponentRigidBody *
ComponentRigidBody_new_ptr(ComponentPosition *component_position) {
  ComponentRigidBody *component_rigid_body = malloc(sizeof(ComponentRigidBody));
  component_rigid_body->base.type = ComponentTypeRigidBody;
  component_rigid_body->base._tick_func = ComponentRigidBody_tick;
  component_rigid_body->_component_position = component_position;
  return component_rigid_body;
}