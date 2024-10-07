#include "./entity_ship.h"
#include "entity.h"

EntityShip EntityShip_new() {
  Entity base = {
    .type = EntityTypeShip,
    .pos = V_0,
  };

  return (EntityShip){
    .base = base,
  };
}
