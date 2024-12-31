#include "entity_ship.h"

#include "game/entity/entity.h"

void EntityShip_tick(Entity *entity) {
  
}

EntityShip EntityShip_new() {
  Entity base = {
      .type = EntityTypeShip,
      .pos = V_0,
      .id = Id_new(),
  };

  base._tickFunc = EntityShip_tick;

  return (EntityShip){
      .base = base,
  };
}
