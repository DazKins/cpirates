#include "entity_renderer_player_ship.h"

#include <stdio.h>

#include "render/model/model_builder.h"
#include "render/model/ship_model.h"

EntityRendererPlayerShip
EntityRendererPlayerShip_new(EntityPlayerShip *entity_player_ship) {
  EntityRenderer base = {.entity = (Entity *)entity_player_ship};

  ModelBuilder model_builder = ModelBuilder_new();
  ShipModel_build(&model_builder);
  Model *model = ModelBuilder_build(&model_builder);

  return (EntityRendererPlayerShip){.base = base, .model = model};
}

void EntityRendererPlayerShip_render(
    EntityRendererPlayerShip *entity_renderer_player_ship,
    RenderContext *render_context) {
  EntityPlayerShip *entity_player_ship =
      (EntityPlayerShip *)entity_renderer_player_ship->base.entity;

  MStack_push(&render_context->matrix_stack,
              M_Translate(entity_player_ship->base.pos));

  RenderContext_render(render_context, entity_renderer_player_ship->model);

  MStack_pop(&render_context->matrix_stack);
}
