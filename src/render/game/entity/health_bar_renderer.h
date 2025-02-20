#ifndef HEALTH_BAR_RENDERER_H
#define HEALTH_BAR_RENDERER_H

#include "game/entity/entity.h"
#include "render/render_context.h"
#include "render/shader.h"
#include <glad/glad.h>

typedef struct {
  Shader shader;
  GLuint vao;
  GLuint vbo;
} HealthBarRenderer;

HealthBarRenderer HealthBarRenderer_new();
void HealthBarRenderer_render(HealthBarRenderer *renderer, Entity *entity,
                              RenderContext *render_context);

#endif // !HEALTH_BAR_RENDERER_H