#include "entity_renderer_ship.h"

#include <stdio.h>

#include "render/model/model_builder.h"
#include "render/model/ship_model.h"

void EntityRendererShip_render(EntityRenderer *entity_renderer,
                               RenderContext *render_context) {
  EntityRendererShip *entity_renderer_ship = (EntityRendererShip *)entity_renderer;

  EntityShip *entity_ship = (EntityShip *)entity_renderer_ship->base.entity;

  MStack_push(&render_context->matrix_stack,
              M_Translate(entity_ship->base.pos));

  RenderContext_render(render_context, entity_renderer_ship->model);
}

EntityRendererShip EntityRendererShip_new(EntityShip *entity_ship) {
  EntityRenderer base = {.entity = (Entity *)entity_ship};

  base._renderFunc = EntityRendererShip_render;

  ModelBuilder model_builder = ModelBuilder_new();
  ShipModel_build(&model_builder);
  Model *model = ModelBuilder_build(&model_builder);

  return (EntityRendererShip){.base = base, .model = model};
}
