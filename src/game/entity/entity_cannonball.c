#include "entity_cannonball.h"

#include <stdio.h>

#include "game/entity/component/component_collider.h"
#include "game/entity/component/component_position.h"
#include "game/entity/component/component_rigid_body.h"

void EntityCannonball_on_collide(Entity *entity) {}

Entity *EntityCannonball_new_ptr() {
  Entity *entity = Entity_new_ptr(EntityTypeCannonball);

  ComponentPosition *component_position = ComponentPosition_new_ptr();
  Entity_add_component(entity, (Component *)component_position);

  ComponentRigidBody *component_rigid_body =
      ComponentRigidBody_new_ptr(component_position);
  Entity_add_component(entity, (Component *)component_rigid_body);

  ComponentCollider *component_collider = ComponentCollider_new_ptr(
      component_position, EntityCannonball_on_collide,
      OBB_new_sym(V_new(0.5f, 0.5f, 0.5f), (V[]){V_x, V_y, V_z}));
  Entity_add_component(entity, (Component *)component_collider);

  return entity;
}