#include "game.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entity/component/component_artillery.h"
#include "entity/component/component_collider.h"
#include "entity/component/component_position.h"
#include "entity/component/component_rigid_body.h"
#include "entity/component/component_team.h"
#include "game/entity/entity_ship.h"
#include "util/id.h"
#include "util/input.h"
#include "util/keys.h"
#include "util/list.h"
#include "util/log.h"
#include "util/tim3.h"

List _Game_entities;
List _Game_entity_ids_marked_for_deletion;
Camera Game_camera;

Entity *player_ship;
Entity *ship_0;
int _current_fire_side; // 0 for right, 1 for left

void Game_add_entity(Entity *entity) { List_push(&_Game_entities, entity); }

List Game_get_entities() { return _Game_entities; }

Entity *Game_spawn_ship_at_position(V position, Team team) {
  Entity *ship = EntityShip_new_ptr(team);
  ComponentPosition *ship_position =
      (ComponentPosition *)Entity_get_component(ship, ComponentTypePosition);
  ship_position->pos = position;
  Game_add_entity(ship);
  return ship;
}

void Game_spawn_random_ships(int count) {
  for (int i = 0; i < count; i++) {
    // Generate random x and z coordinates between -20 and 20
    float x = (float)(rand() % 41 - 20); // -20 to 20
    float z = (float)(rand() % 41 - 20); // -20 to 20

    // Alternate between red and blue teams
    Team team = (i % 2 == 0) ? TeamRed : TeamBlue;
    Game_spawn_ship_at_position(V_new(x, 0.0f, z), team);
  }
}

int Game_init() {
  srand(time(NULL)); // Initialize random seed

  _Game_entities = List_new();
  _Game_entity_ids_marked_for_deletion = List_new();
  _current_fire_side = 0; // Start firing right

  // Create player ship (red team)
  player_ship = EntityShip_new_ptr(TeamRed);
  Game_add_entity(player_ship);

  // Spawn 5 random ships for testing
  Game_spawn_random_ships(5);

  Game_camera = Camera_new(1280.0f / 720.0f, M_PI / 2.0f, 0.01f, 100.0f);

  return 0;
}

void Game_handle_entity_collisions() {
  // Just iterate over all entities for now; spatial optimisation can be added
  // in the future.
  Iterator entities_iter_0 = Iterator_new(&_Game_entities);
  while (Iterator_has_next(&entities_iter_0)) {
    Entity *entity_0 = Iterator_next(&entities_iter_0);

    ComponentCollider *component_collider_0 =
        (ComponentCollider *)Entity_get_component(entity_0,
                                                  ComponentTypeCollider);
    if (component_collider_0 == NULL)
      continue;

    // Get the oriented bounding box for the first entity.
    OBB obb_0 = ComponentCollider_get_obb(component_collider_0);

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

      // Get the oriented bounding box for the second entity.
      OBB obb_1 = ComponentCollider_get_obb(component_collider_1);

      // Check for collision using the Separating Axis Theorem.
      if (OBB_intersects(obb_0, obb_1)) {
        ComponentCollider_on_collide(component_collider_0, entity_0, entity_1);
      }
    }
  }
}

const float MAX_ELEVATION = 0.35f * M_PI;
const float MIN_ELEVATION = 0.1f * M_PI;

float dist = 10.0f;
float azimuth = M_PI;
float elevation = 0.2f * M_PI;

void Game_mark_entity_for_deletion(Id entity_id) {
  Id *entity_id_ptr = malloc(sizeof(Id));
  *entity_id_ptr = entity_id;
  List_push(&_Game_entity_ids_marked_for_deletion, entity_id_ptr);
}

void Game_remove_marked_entities() {
  Iterator iter = Iterator_new(&_Game_entity_ids_marked_for_deletion);
  while (Iterator_has_next(&iter)) {
    Id *entity_id = Iterator_next(&iter);

    // Find and remove entity with matching ID
    Iterator entities_iter = Iterator_new(&_Game_entities);
    while (Iterator_has_next(&entities_iter)) {
      Entity *entity = Iterator_next(&entities_iter);
      if (Id_eq(entity->id, *entity_id)) {
        List_remove(&_Game_entities, entity);
        break;
      }
    }
  }

  // Clear the marked for deletion list
  List_clear(&_Game_entity_ids_marked_for_deletion);
}

void Game_tick() {
  Log_trace("Removing marked entities...");
  // Remove marked entities at the start of each tick
  Game_remove_marked_entities();
  Log_trace("Marked entities removed");

  Log_trace("Ticking entities...");
  Iterator entities_iter = Iterator_new(&_Game_entities);
  while (Iterator_has_next(&entities_iter)) {
    Entity *entity = Iterator_next(&entities_iter);
    Entity_tick(entity);
  }
  Log_trace("Entities ticked");

  Log_trace("Handling entity collisions...");
  Game_handle_entity_collisions();
  Log_trace("Entity collisions handled");

  Log_trace("Updating camera...");
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
  Log_trace("Camera updated");

  Log_trace("Checking for artillery fire...");
  if (Input_is_key_down(KEY_SPACE)) {
    Log_trace("Artillery fire detected");
    ComponentArtillery *artillery = (ComponentArtillery *)Entity_get_component(
        player_ship, ComponentTypeArtillery);
    ComponentPosition *position = (ComponentPosition *)Entity_get_component(
        player_ship, ComponentTypePosition);
    V rot = ComponentPosition_get_rot(position);

    // Calculate firing direction based on current side
    V direction;
    if (_current_fire_side == 0) { // Right side
      direction = V_new(-cos(rot.y), 0.0f, -sin(rot.y));
    } else { // Left side
      direction = V_new(cos(rot.y), 0.0f, sin(rot.y));
    }

    if (ComponentArtillery_fire(artillery, direction) ==
        ArtilleryFireResponseSuccess) {
      _current_fire_side =
          !_current_fire_side; // Toggle side after successful fire
    }
  }
  Log_trace("Artillery fire checked");

  if (elevation > MAX_ELEVATION) {
    elevation = MAX_ELEVATION;
  }
  if (elevation < MIN_ELEVATION) {
    elevation = MIN_ELEVATION;
  }

  Log_trace("Moving player ship...");
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
                            V_norm(push_vector), 0.002f);
  }
  Log_trace("Player ship moved");
}
