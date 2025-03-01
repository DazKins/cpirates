#include "entity_renderer.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/entity/component/component_collider.h"
#include "game/entity/component/component_position.h"
#include "render/debug/debug.h"
#include "render/game/entity/entity_renderer_basic_model.h"
#include "render/model/model_builder.h"
#include "render/model/model_cannonball.h"
#include "render/model/model_ship.h"
#include "util/config.h"

EntityRenderer *EntityRenderer_new_ptr(Entity *entity) {
  EntityRenderer *entity_renderer;

  switch (entity->type) {
  case EntityTypeShip: {
    EntityRendererBasicModel *entity_renderer =
        malloc(sizeof(EntityRendererBasicModel));

    Model *model_ship = ModelShip_build();

    *entity_renderer = EntityRendererBasicModel_new(entity, model_ship);
    return (EntityRenderer *)entity_renderer;
  }
  case EntityTypeCannonball: {
    EntityRendererBasicModel *entity_renderer =
        malloc(sizeof(EntityRendererBasicModel));

    Model *model_cannonball = ModelCannonball_build();

    *entity_renderer = EntityRendererBasicModel_new(entity, model_cannonball);
    return (EntityRenderer *)entity_renderer;
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

  if (Config_debug) {
    ComponentPosition *entity_component_position =
        (ComponentPosition *)Entity_get_component(entity_renderer->entity,
                                                  ComponentTypePosition);
    if (entity_component_position != NULL) {
      DebugRender_point(entity_component_position->pos, 0.2f);
    }

    ComponentCollider *entity_component_collider =
        (ComponentCollider *)Entity_get_component(entity_renderer->entity,
                                                  ComponentTypeCollider);
    if (entity_component_collider != NULL) {
      DebugRender_obb(ComponentCollider_get_obb(entity_component_collider));
    }
  }
}
