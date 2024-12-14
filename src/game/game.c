#include "game.h"

#include <stdlib.h>

#include "util/list.h"
#include "game/entity/entity_ship.h"

List Game_entities;

EntityShip *ship_0;
EntityShip *ship_1;

int Game_init() {
  Game_entities = List_new();

  ship_0 = malloc(sizeof(EntityShip));
  *ship_0 = EntityShip_new();

  List_push(&Game_entities, ship_0);

  ship_1 = malloc(sizeof(EntityShip));
  *ship_1 = EntityShip_new();

  List_push(&Game_entities, ship_1);

  return 0;
}

int i = 0;

void Game_tick() {
  i++;

  ship_1->base.pos=V_new(2.0f + (float) i / 500.0f, 0.0f, 0.0f);
}
