#include "entity_player_ship.h"

#include <stdio.h>

#include "game/entity/entity.h"
#include "util/keys.h"
#include "util/input.h"

void EntityPlayerShip_push(EntityPlayerShip *entity_player_ship,
                           V push_direction, float push_force) {
  entity_player_ship->base.vel =
      V_add(entity_player_ship->base.vel, V_mul(push_direction, push_force));
}

void EntityPlayerShip_tick(Entity *entity) {
  EntityPlayerShip *entity_player_ship = (EntityPlayerShip *)entity;

  // if (Input_is_key_down(KEY_W)) {
  //   entity_player_ship->base.pos.z -= 0.01f;
  // }
  // if (Input_is_key_down(KEY_S)) {
  //   entity_player_ship->base.pos.z += 0.01f;
  // }
  // if (Input_is_key_down(KEY_A)) {
  //   entity_player_ship->base.pos.x -= 0.01f;
  // }
  // if (Input_is_key_down(KEY_D)) {
  //   entity_player_ship->base.pos.x += 0.01f;
  // }

  entity_player_ship->base.pos =
      V_add(entity_player_ship->base.pos, entity_player_ship->base.vel);

  entity_player_ship->base.vel = V_mul(entity_player_ship->base.vel, 0.9f);
}

EntityPlayerShip EntityPlayerShip_new() {
  Entity base = {
      .type = EntityTypePlayerShip, .pos = V_0, .vel = V_0, .id = Id_new()};

  base._tickFunc = EntityPlayerShip_tick;

  return (EntityPlayerShip){
      .base = base,
  };
}
