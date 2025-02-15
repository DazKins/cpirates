#include "entity_ship.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/entity/component/component_artillery.h"
#include "game/entity/component/component_collider.h"
#include "game/entity/component/component_health.h"
#include "game/entity/component/component_position.h"
#include "game/entity/component/component_rigid_body.h"

#include "util/log.h"

void EntityShip_on_collide(Entity *entity, Entity *hit_entity) {
  // Only take damage from cannonballs
  if (hit_entity->type != EntityTypeCannonball) {
    return;
  }

  // Check if this cannonball was fired by us
  Id *fired_by = HashMap_get(hit_entity->metadata, "fired_by");
  if (fired_by != NULL && Id_eq(*fired_by, entity->id)) {
    return;  // Don't take damage from our own cannonballs
  }

  Log("Ship hit by cannonball");

  // Get the health component
  ComponentHealth *component_health =
      (ComponentHealth *)Entity_get_component(entity, ComponentTypeHealth);

  if (component_health != NULL) {
    // Apply damage when hit by a cannonball
    ComponentHealth_damage(component_health, 20);
  }
}

Entity *EntityShip_new_ptr() {
  Entity *entity = Entity_new_ptr(EntityTypeShip);

  Id id = entity->id;

  ComponentPosition *component_position = ComponentPosition_new_ptr(id);
  Entity_add_component(entity, (Component *)component_position);

  ComponentRigidBody *component_rigid_body =
      ComponentRigidBody_new_ptr(id, component_position);
  Entity_add_component(entity, (Component *)component_rigid_body);

  ComponentArtillery *component_artillery =
      ComponentArtillery_new_ptr(id, component_position, 160);
  Entity_add_component(entity, (Component *)component_artillery);

  ComponentCollider *component_collider = ComponentCollider_new_ptr(
      id, component_position, EntityShip_on_collide,
      OBB_new(V_new(0.0f, 0.5f, 0.0f), V_new(1.0f, 0.7f, 1.5f),
              (V[]){V_x, V_y, V_z}));
  Entity_add_component(entity, (Component *)component_collider);

  ComponentHealth *component_health = ComponentHealth_new_ptr(id, 100);
  Entity_add_component(entity, (Component *)component_health);

  return entity;
}
