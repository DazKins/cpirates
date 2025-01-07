#include "entity_renderer_basic_model.h"

#include <stdio.h>

#include "game/entity/component/component_position.h"
#include "render/model/model_builder.h"
#include "render/model/model_ship.h"

void EntityRendererBasicModel_render(EntityRenderer *entity_renderer,
                                     RenderContext *render_context) {
  EntityRendererBasicModel *entity_renderer_basic_model =
      (EntityRendererBasicModel *)entity_renderer;

  Entity *entity = entity_renderer_basic_model->base.entity;

  ComponentPosition *entity_component_position =
      (ComponentPosition *)Entity_get_component(entity, ComponentTypePosition);
  if (entity_component_position != NULL) {
    M transform = M_I(4);

    V rot = ComponentPosition_get_rot(entity_component_position);

    transform = M_mul(transform, M_Translate(entity_component_position->pos));
    transform = M_mul(transform, M_RotX(rot.x));
    transform = M_mul(transform, M_RotY(rot.y));
    transform = M_mul(transform, M_RotZ(rot.z));

    MStack_push(&render_context->matrix_stack, transform);
  }

  RenderContext_render(render_context, entity_renderer_basic_model->model);

  MStack_pop(&render_context->matrix_stack);
}

EntityRendererBasicModel EntityRendererBasicModel_new(Entity *entity,
                                                      Model *model) {
  EntityRenderer base = {.entity = entity};

  base._renderFunc = EntityRendererBasicModel_render;

  return (EntityRendererBasicModel){.base = base, .model = model};
}
