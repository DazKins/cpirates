#include "game.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "entity/component/component_artillery.h"
#include "entity/component/component_collider.h"
#include "entity/component/component_position.h"
#include "entity/component/component_rigid_body.h"
#include "game/entity/entity_ship.h"
#include "util/input.h"
#include "util/keys.h"
#include "util/list.h"

List _Game_entities;
Camera Game_camera;

Entity *player_ship;
Entity *ship_0;

void Game_add_entity(Entity *entity) { List_push(&_Game_entities, entity); }

List Game_get_entities() { return _Game_entities; }

int Game_init() {
  _Game_entities = List_new();

  player_ship = EntityShip_new_ptr();
  Game_add_entity(player_ship);

  ship_0 = EntityShip_new_ptr();
  Game_add_entity(ship_0);

  Game_camera = Camera_new(1280.0f / 720.0f, M_PI / 2.0f, 0.01f, 100.0f);

  return 0;
}

void Game_handle_entity_collisions() {
  // just iterate over all entities for now, will need spatial optimisation in
  // future
  Iterator entities_iter_0 = Iterator_new(&_Game_entities);
  while (Iterator_has_next(&entities_iter_0)) {
    Entity *entity_0 = Iterator_next(&entities_iter_0);

    ComponentCollider *component_collider_0 =
        (ComponentCollider *)Entity_get_component(entity_0,
                                                  ComponentTypeCollider);

    if (component_collider_0 == NULL)
      continue;

    AABB aabb_0 = ComponentCollider_get_aabb(component_collider_0);

    Iterator entities_iter_1 = Iterator_new(&_Game_entities);
    while (Iterator_has_next(&entities_iter_1)) {
      Entity *entity_1 = Iterator_next(&entities_iter_1);

      if (entity_0 == entity_1)
        continue;

      ComponentCollider *component_collider_1 =
          (ComponentCollider *)Entity_get_component(entity_1,
                                                    ComponentTypeCollider);

      if (component_collider_1 == NULL)
        continue;

      AABB aabb_1 = ComponentCollider_get_aabb(component_collider_1);

      if (AABB_contains(aabb_0, aabb_1)) {
        printf("entity 0: %s, entity 1: %s\n", Id_to_string(entity_0->id),
               Id_to_string(entity_1->id));
        printf("aabb 0: %s, aabb 1: %s\n", AABB_to_string(aabb_0),
               AABB_to_string(aabb_1));
        ComponentCollider_on_collide(component_collider_0, entity_1);
      }
    }
  }
}

int i = 0;

const float MAX_ELEVATION = 0.35f * M_PI;
const float MIN_ELEVATION = 0.1f * M_PI;

float dist = 10.0f;
float azimuth = M_PI;
float elevation = 0.2f * M_PI;

void Game_tick() {
  Iterator entities_iter = Iterator_new(&_Game_entities);
  while (Iterator_has_next(&entities_iter)) {
    Entity *entity = Iterator_next(&entities_iter);
    Entity_tick(entity);
  }

  Game_handle_entity_collisions();

  if (Input_is_key_down(KEY_UP)) {
    elevation += 0.01f;
  }
  if (Input_is_key_down(KEY_DOWN)) {
    elevation -= 0.01f;
  }
  if (Input_is_key_down(KEY_LEFT)) {
    azimuth += 0.01f;
  }
  if (Input_is_key_down(KEY_RIGHT)) {
    azimuth -= 0.01f;
  }

  if (Input_is_key_down(KEY_SPACE)) {
    ComponentArtillery_fire((ComponentArtillery *)Entity_get_component(
        player_ship, ComponentTypeArtillery));
  }

  if (elevation > MAX_ELEVATION) {
    elevation = MAX_ELEVATION;
  }
  if (elevation < MIN_ELEVATION) {
    elevation = MIN_ELEVATION;
  }

  ComponentPosition *player_ship_component_position =
      (ComponentPosition *)Entity_get_component(player_ship,
                                                ComponentTypePosition);
  Camera_look_at(&Game_camera, player_ship_component_position->pos, dist,
                 azimuth, elevation);

  V look_vector = Camera_get_look_vector(&Game_camera);
  V flat_facing_direction = V_norm(V_set_y(look_vector, 0.0f));
  V push_vector = V_0;

  if (Input_is_key_down(KEY_W)) {
    push_vector.x += flat_facing_direction.x;
    push_vector.z += flat_facing_direction.z;
  }
  if (Input_is_key_down(KEY_S)) {
    push_vector.x -= flat_facing_direction.x;
    push_vector.z -= flat_facing_direction.z;
  }
  if (Input_is_key_down(KEY_A)) {
    push_vector.x += flat_facing_direction.z;
    push_vector.z += -flat_facing_direction.x;
  }
  if (Input_is_key_down(KEY_D)) {
    push_vector.x += -flat_facing_direction.z;
    push_vector.z += flat_facing_direction.x;
  }

  if (!V_eq(push_vector, V_0)) {
    ComponentRigidBody *player_ship_component_rigid_body =
        (ComponentRigidBody *)Entity_get_component(player_ship,
                                                   ComponentTypeRigidBody);
    ComponentRigidBody_push(player_ship_component_rigid_body,
                            V_norm(push_vector), 0.01f);
  }

  i++;
  ComponentPosition *ship_0_component_position =
      (ComponentPosition *)Entity_get_component(ship_0, ComponentTypePosition);
  ship_0_component_position->pos = V_new(2.0f + (float)i / 500.0f, 0.0f, 0.0f);
  ComponentPosition_set_rot(ship_0_component_position,
                            V_new(0.0f, 2.0f + (float)i / 500.0f, 0.0f));
}
