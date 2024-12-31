#include "game.h"

#include <stdlib.h>
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

float az = 0.0f;
float el = 0.0f;

void Game_tick() {
  // Camera_process_input(&Game_camera);

  if (Input_is_key_down(KEY_UP)) {
    el += 0.01f;
  }
  if (Input_is_key_down(KEY_DOWN)) {
    el -= 0.01f;
  }
  if (Input_is_key_down(KEY_LEFT)) {
    az -= 0.01f;
  }
  if (Input_is_key_down(KEY_RIGHT)) {
    az += 0.01f;
  }

  Camera_look_at(&Game_camera, player_ship->base.pos, 5.0f, az, el);

  i++;

  ship_0->base.pos=V_new(2.0f + (float) i / 500.0f, 0.0f, 0.0f);
}
