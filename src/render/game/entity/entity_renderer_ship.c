#include "entity_renderer_ship.h"

#include <stdio.h>

#include "game/entity/component/component_position.h"
#include "render/model/model_builder.h"
#include "render/model/ship_model.h"

void EntityRendererShip_render(EntityRenderer *entity_renderer,
                               RenderContext *render_context) {
  EntityRendererShip *entity_renderer_ship =
      (EntityRendererShip *)entity_renderer;

  Entity *entity = entity_renderer_ship->base.entity;

  ComponentPosition *entity_component_position =
      Entity_get_component(entity, ComponentTypePosition);
  if (entity_component_position != NULL) {
    printf("EntityRendererShip_render: entity_component_position->pos: %s\n",
           V_to_string(entity_component_position->pos));
    MStack_push(&render_context->matrix_stack,
                M_Translate(entity_component_position->pos));
  }

  RenderContext_render(render_context, entity_renderer_ship->model);

  MStack_pop(&render_context->matrix_stack);
}

EntityRendererShip EntityRendererShip_new(Entity *entity) {
  EntityRenderer base = {.entity = entity};

  base._renderFunc = EntityRendererShip_render;

  ModelBuilder model_builder = ModelBuilder_new();
  ShipModel_build(&model_builder);
  Model *model = ModelBuilder_build(&model_builder);

  return (EntityRendererShip){.base = base, .model = model};
}
