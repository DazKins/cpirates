#include "entity_player_ship.h"

#include "game/entity/entity.h"

EntityPlayerShip EntityPlayerShip_new() {
  Entity base = {
      .type = EntityTypePlayerShip,
      .pos = V_0,
      .id = Id_new()
  };

  return (EntityPlayerShip){
      .base = base,
  };
}
