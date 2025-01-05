#include "entity_renderer.h"

#include <stdio.h>
#include <stdlib.h>

#include "render/game/entity/entity_renderer_ship.h"

EntityRenderer *EntityRenderer_new_ptr(Entity *entity) {
  EntityRenderer *entity_renderer;

  switch (entity->type) {
  case EntityTypeShip: {
    EntityRendererShip *entityRenderer = malloc(sizeof(EntityRendererShip));
    *entityRenderer = EntityRendererShip_new(entity);
    return (EntityRenderer *)entityRenderer;
  }
  default: {
    printf("no renderer for entity type %d\n", entity->type);
    return NULL;
  }
  }
}

void EntityRenderer_render(EntityRenderer *entity_renderer,
                           RenderContext *render_context) {
  entity_renderer->_renderFunc(entity_renderer, render_context);
}
