#include "entity_ship.h"

#include <stdio.h>

#include "render/model/model_builder.h"
#include "render/model/ship_model.h"

EntityRendererShip EntityRendererShip_new(EntityShip *entity_ship) {
  EntityRenderer base = {.entity = entity_ship};

  ModelBuilder model_builder = ModelBuilder_new();
  ShipModel_build(&model_builder);
  Model *model = ModelBuilder_build(&model_builder);

  return (EntityRendererShip){.base = base, .model = model};
}

void EntityRendererShip_render(EntityRendererShip *entity_renderer_ship,
                               RenderContext *render_context) {
  EntityShip *entity_ship = entity_renderer_ship->base.entity;

  MStack_push(&render_context->matrix_stack,
              M_Translate(entity_ship->base.pos));

  RenderContext_render(render_context, entity_renderer_ship->model);
}
