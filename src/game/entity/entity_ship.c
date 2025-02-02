#include "entity_ship.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/entity/component/component_artillery.h"
#include "game/entity/component/component_collider.h"
#include "game/entity/component/component_position.h"
#include "game/entity/component/component_rigid_body.h"

void EntityShip_on_collide(Entity *entity) { printf("ship collision!\n"); }

Entity *EntityShip_new_ptr() {
  Entity *entity = Entity_new_ptr(EntityTypeShip);

  ComponentPosition *component_position = ComponentPosition_new_ptr();
  Entity_add_component(entity, (Component *)component_position);

  ComponentRigidBody *component_rigid_body =
      ComponentRigidBody_new_ptr(component_position);
  Entity_add_component(entity, (Component *)component_rigid_body);

  ComponentArtillery *component_artillery =
      ComponentArtillery_new_ptr(component_position, 160);
  Entity_add_component(entity, (Component *)component_artillery);

  ComponentCollider *component_collider = ComponentCollider_new_ptr(
      component_position, EntityShip_on_collide,
      AABB_new(V_new(-0.5f, -0.5f, -0.5f), V_new(0.5f, 0.5f, 0.5f)));
  Entity_add_component(entity, (Component *)component_collider);

  return entity;
}
