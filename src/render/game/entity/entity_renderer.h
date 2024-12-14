#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "game/entity/entity.h"
#include "game/entity/entity.h"

#include "render/render_context.h"

#include "util/id.h"

typedef struct {
  Entity *entity;
} EntityRenderer;

EntityRenderer *EntityRenderer_new_ptr(Entity *entity);

void EntityRenderer_render(EntityRenderer *entity_renderer, RenderContext *rc);

#endif // !ENTITY_RENDERER_H
