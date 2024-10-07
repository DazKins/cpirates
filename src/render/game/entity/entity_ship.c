#include "entity_ship.h"

EntityRendererShip EntityRendererShip_new(EntityShip *entity_ship) {
  EntityRenderer base = {};

  return (EntityRendererShip){base};
}
