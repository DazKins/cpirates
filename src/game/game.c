#include "game.h"

#include "../util/list.h"
#include "entity/entity_ship.h"
#include <stdlib.h>

List Game_entities;

int Game_init() {
  Game_entities = List_new();

  EntityShip *player_ship = malloc(sizeof(EntityShip));
  *player_ship = EntityShip_new();

  List_push(&Game_entities, player_ship);

  return 0;
}

void Game_tick() {}
