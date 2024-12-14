#include "entity_renderer.h"

#include <stdlib.h>
#include <stdio.h>

#include "render/game/entity/entity_renderer_ship.h"

EntityRenderer *EntityRenderer_new_ptr(Entity *entity) {
  EntityRenderer *entity_renderer;

  switch (entity->type) {
  case EntityTypeShip: {
    EntityRendererShip *entityRenderer = malloc(sizeof(EntityRendererShip));
    *entityRenderer = EntityRendererShip_new((EntityShip *)entity);
    return (EntityRenderer *)entityRenderer;
  }
  default: {
    printf("no renderer for entity type %d\n", entity->type);
    return NULL;
  }
  }
}

void EntityRenderer_render(EntityRenderer *entity_renderer, RenderContext *rc) {
  switch (entity_renderer->entity->type) {
  case EntityTypeShip: {
    EntityRendererShip_render((EntityRendererShip *)entity_renderer, rc);
    break;
  }
  }
}
