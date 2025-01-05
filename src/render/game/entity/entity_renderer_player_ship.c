#include "entity_renderer_player_ship.h"

#include <stdio.h>

#include "game/entity/component/component_position.h"
#include "render/model/model_builder.h"
#include "render/model/ship_model.h"

void EntityRendererPlayerShip_render(EntityRenderer *entity_renderer,
                                     RenderContext *render_context) {
  EntityRendererPlayerShip *entity_renderer_player_ship =
      (EntityRendererPlayerShip *)entity_renderer;

  Entity *entity = entity_renderer_player_ship->base.entity;

  ComponentPosition *entity_component_position =
      Entity_get_component(entity, ComponentTypePosition);
  if (entity_component_position != NULL) {
    MStack_push(&render_context->matrix_stack,
                M_Translate(entity_component_position->pos));
  }

  RenderContext_render(render_context, entity_renderer_player_ship->model);

  MStack_pop(&render_context->matrix_stack);
}

EntityRendererPlayerShip EntityRendererPlayerShip_new(Entity *entity) {
  EntityRenderer base = {.entity = entity};

  base._renderFunc = EntityRendererPlayerShip_render;

  ModelBuilder model_builder = ModelBuilder_new();
  ShipModel_build(&model_builder);
  Model *model = ModelBuilder_build(&model_builder);

  return (EntityRendererPlayerShip){.base = base, .model = model};
}
