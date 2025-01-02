#include "game.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "util/input.h"
#include "util/list.h"
#include "game/entity/entity_ship.h"
#include "game/entity/entity_player_ship.h"
#include "util/keys.h"

List Game_entities;
Camera Game_camera;

EntityPlayerShip *player_ship;
EntityShip *ship_0;

int Game_init() {
  Game_entities = List_new();

  player_ship = malloc(sizeof(EntityPlayerShip));
  *player_ship = EntityPlayerShip_new();

  List_push(&Game_entities, player_ship);

  ship_0 = malloc(sizeof(EntityShip));
  *ship_0 = EntityShip_new();

  List_push(&Game_entities, ship_0);

  Game_camera = Camera_new(1280.0f / 720.0f, M_PI / 2.0f, 0.01f, 100.0f);

  return 0;
}

int i = 0;

const float MAX_ELEVATION = 0.35f * M_PI;
const float MIN_ELEVATION = 0.1f * M_PI;

float azimuth = 0.0f;
float elevation = 0.2f * M_PI;

void Game_tick() {
  Iterator entities_iter = Iterator_new(&Game_entities);
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
    azimuth -= 0.01f;
  }
  if (Input_is_key_down(KEY_RIGHT)) {
    azimuth += 0.01f;
  }

  if (elevation > MAX_ELEVATION) {
    elevation = MAX_ELEVATION;
  }
  if (elevation < MIN_ELEVATION) {
    elevation = MIN_ELEVATION;
  }

  Camera_look_at(&Game_camera, player_ship->base.pos, 5.0f, azimuth, elevation);

  V look_vector = Camera_get_look_vector(&Game_camera);
  V push_vector = V_norm(V_set_y(look_vector, 0));

  if (Input_is_key_down(KEY_W)) {
    EntityPlayerShip_push(player_ship, push_vector, 0.01f);
  }
  if (Input_is_key_down(KEY_S)) {
    EntityPlayerShip_push(player_ship, V_neg(&push_vector), 0.01f);
  }

  i++;

  ship_0->base.pos=V_new(2.0f + (float) i / 500.0f, 0.0f, 0.0f);
}
