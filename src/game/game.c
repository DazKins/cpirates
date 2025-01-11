#include "game.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "entity/component/component_artillery.h"
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

  int key_down = 0;

  if (Input_is_key_down(KEY_W)) {
    key_down = 1;
    push_vector = V_add(push_vector, flat_facing_direction);
  }
  if (Input_is_key_down(KEY_S)) {
    key_down = 1;
    push_vector = V_add(push_vector, V_neg(flat_facing_direction));
  }
  if (Input_is_key_down(KEY_A)) {
    key_down = 1;
    float tmp_x = flat_facing_direction.x;
    flat_facing_direction.x = flat_facing_direction.z;
    flat_facing_direction.z = -tmp_x;

    push_vector = V_add(push_vector, flat_facing_direction);
  }
  if (Input_is_key_down(KEY_D)) {
    key_down = 1;
    float tmp_x = flat_facing_direction.x;
    flat_facing_direction.x = -flat_facing_direction.z;
    flat_facing_direction.z = tmp_x;

    push_vector = V_add(push_vector, flat_facing_direction);
  }

  if (key_down) {
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
