#include "entity_cannonball.h"
#include "component/component_position.h"
#include "component/component_rigid_body.h"

Entity *EntityCannonball_new_ptr() {
  Entity *entity = Entity_new_ptr(EntityTypeCannonball);

  ComponentPosition *component_position = ComponentPosition_new_ptr();
  Entity_add_component(entity, (Component *)component_position);

  ComponentRigidBody *component_rigid_body =
      ComponentRigidBody_new_ptr(component_position);
  Entity_add_component(entity, (Component *)component_rigid_body);

  return entity;
}