#include "entity.h"

#include <stdlib.h>

#include "render/game/entity/entity_ship.h"
#include "render/render_context.h"

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

void EntityRenderer_render(RenderContext *rc) {
  
}
