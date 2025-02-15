#include "entity_cannonball.h"

#include <stdio.h>

#include "game/entity/component/component_collider.h"
#include "game/entity/component/component_lifetime.h"
#include "game/entity/component/component_position.h"
#include "game/entity/component/component_rigid_body.h"
#include "game/entity/component/component_team.h"
#include "game/game.h"
#include "util/id.h"

void EntityCannonball_on_collide(Entity *entity, Entity *hit_entity) {
  // Get the ID of the entity that fired this cannonball
  Id *fired_by = HashMap_get(entity->metadata, "fired_by");

  // If the cannonball was fired by an entity and it's the same as the hit
  // entity, return
  if (fired_by != NULL && Id_eq(*fired_by, hit_entity->id)) {
    return;
  }

  // Only delete cannonball if it hits a ship
  if (hit_entity->type == EntityTypeShip) {
    Game_mark_entity_for_deletion(entity->id);
  }
}

Entity *EntityCannonball_new_ptr(Team team) {
  Entity *entity = Entity_new_ptr(EntityTypeCannonball);

  Id id = entity->id;

  ComponentPosition *component_position = ComponentPosition_new_ptr(id);
  Entity_add_component(entity, (Component *)component_position);

  ComponentRigidBody *component_rigid_body =
      ComponentRigidBody_new_ptr(id, component_position);
  Entity_add_component(entity, (Component *)component_rigid_body);

  ComponentCollider *component_collider = ComponentCollider_new_ptr(
      id, component_position, EntityCannonball_on_collide,
      OBB_new_sym(V_new(0.5f, 0.5f, 0.5f), (V[]){V_x, V_y, V_z}));
  Entity_add_component(entity, (Component *)component_collider);

  ComponentLifetime *component_lifetime = ComponentLifetime_new_ptr(id, 50);
  Entity_add_component(entity, (Component *)component_lifetime);

  ComponentTeam *component_team = ComponentTeam_new_ptr(id, team);
  Entity_add_component(entity, (Component *)component_team);

  return entity;
}