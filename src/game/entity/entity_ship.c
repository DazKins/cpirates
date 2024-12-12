#include "entity_ship.h"

#include "game/entity/entity.h"

EntityShip EntityShip_new() {
  Entity base = {
      .type = EntityTypeShip,
      .pos = V_0,
  };

  return (EntityShip){
      .base = base,
  };
}
