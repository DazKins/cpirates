#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "game/entity/entity.h"

#include "render/render_context.h"

#include "util/id.h"

typedef struct _entityRenderer {
  Entity *entity;

  void (*_renderFunc)(struct _entityRenderer *entity_renderer,
                      RenderContext *render_context);
} EntityRenderer;

EntityRenderer *EntityRenderer_new_ptr(Entity *entity);

void EntityRenderer_render(EntityRenderer *entity_renderer,
                           RenderContext *render_context);

#endif // !ENTITY_RENDERER_H
