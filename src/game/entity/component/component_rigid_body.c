#include "component_rigid_body.h"

void ComponentRigidBody_tick(Component *component) {
  ComponentRigidBody *component_rigid_body = (ComponentRigidBody *)component;

  component_rigid_body->_component_position->pos =
      V_add(component_rigid_body->_component_position->pos,
            component_rigid_body->velocity);

  component_rigid_body->velocity = V_mul(component_rigid_body->velocity, 0.9f);
}

void ComponentRigidBody_push(ComponentRigidBody *component_rigid_body,
                             V push_direction, float push_force) {
  component_rigid_body->velocity =
      V_add(component_rigid_body->velocity, V_mul(push_direction, push_force));
}

ComponentRigidBody
ComponentRigidBody_new(ComponentPosition *component_position) {
  ComponentRigidBody component_rigid_body = {};
  component_rigid_body.base.type = ComponentTypeRigidBody;
  component_rigid_body.base._tick_func = ComponentRigidBody_tick;
  component_rigid_body._component_position = component_position;
  return component_rigid_body;
}