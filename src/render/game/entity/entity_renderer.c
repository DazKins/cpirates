#include "entity_renderer.h"

#include <stdlib.h>
#include <stdio.h>

#include "render/game/entity/entity_renderer_ship.h"
#include "render/game/entity/entity_renderer_player_ship.h"

EntityRenderer *EntityRenderer_new_ptr(Entity *entity) {
  EntityRenderer *entity_renderer;

  switch (entity->type) {
  case EntityTypeShip: {
    EntityRendererShip *entityRenderer = malloc(sizeof(EntityRendererShip));
    *entityRenderer = EntityRendererShip_new((EntityShip *)entity);
    return (EntityRenderer *)entityRenderer;
  }
  case EntityTypePlayerShip: {
    EntityRendererPlayerShip *entityRenderer = malloc(sizeof(EntityRendererPlayerShip));
    *entityRenderer = EntityRendererPlayerShip_new((EntityPlayerShip *)entity);
    return (EntityRenderer *)entityRenderer;
  }
  default: {
    printf("no renderer for entity type %d\n", entity->type);
    return NULL;
  }
  }
}

void EntityRenderer_render(EntityRenderer *entity_renderer, RenderContext *render_context) {
  entity_renderer->_renderFunc(entity_renderer, render_context);
}
