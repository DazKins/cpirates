#include "entity.h"
#include "entity_ship.h"
#include <stdlib.h>

EntityRenderer *EntityRenderer_new_ptr(Entity *entity) {
  EntityRenderer *entity_renderer;

  switch (entity->type) {
  case EntityTypeShip: {
    EntityRendererShip *entityRenderer = malloc(sizeof(EntityRendererShip));
    *entityRenderer = EntityRendererShip_new((EntityShip *)entity);
    return (EntityRenderer *)entityRenderer;
  }
  }
}
