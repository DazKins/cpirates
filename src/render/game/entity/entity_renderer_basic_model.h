#ifndef ENTITY_RENDERER_BASIC_MODEL_H
#define ENTITY_RENDERER_BASIC_MODEL_H

#include "render/game/entity/entity_renderer.h"
#include "render/render_context.h"

typedef struct {
  EntityRenderer base;

  Model *model;
} EntityRendererBasicModel;

EntityRendererBasicModel EntityRendererBasicModel_new(Entity *entity, Model* model);

#endif // !ENTITY_SHIP_RENDER_H
