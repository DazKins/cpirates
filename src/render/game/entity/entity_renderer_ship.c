#include "entity_renderer_ship.h"

#include <stdio.h>

#include "game/entity/component/component_position.h"
#include "render/model/model_builder.h"
#include "render/model/model_ship.h"

void EntityRendererShip_render(EntityRenderer *entity_renderer,
                               RenderContext *render_context) {
  EntityRendererShip *entity_renderer_ship =
      (EntityRendererShip *)entity_renderer;

  Entity *entity = entity_renderer_ship->base.entity;

  ComponentPosition *entity_component_position =
      Entity_get_component(entity, ComponentTypePosition);
  if (entity_component_position != NULL) {
    M transform = M_I(4);

    V rot = ComponentPosition_get_rot(entity_component_position);

    transform = M_mul(transform, M_Translate(entity_component_position->pos));
    transform = M_mul(transform, M_RotX(rot.x));
    transform = M_mul(transform, M_RotY(rot.y));
    transform = M_mul(transform, M_RotZ(rot.z));

    MStack_push(&render_context->matrix_stack, transform);
  }

  RenderContext_render(render_context, entity_renderer_ship->model);

  MStack_pop(&render_context->matrix_stack);
}

EntityRendererShip EntityRendererShip_new(Entity *entity) {
  EntityRenderer base = {.entity = entity};

  base._renderFunc = EntityRendererShip_render;

  ModelBuilder model_builder = ModelBuilder_new();
  ModelShip_build(&model_builder);
  Model *model = ModelBuilder_build(&model_builder);

  return (EntityRendererShip){.base = base, .model = model};
}
