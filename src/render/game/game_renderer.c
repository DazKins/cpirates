#include "game_renderer.h"

#include <stdio.h>

#include "game/entity/entity.h"
#include "render/game/entity/entity_renderer.h"
#include "render/model/model.h"
#include "render/model/model_builder.h"
#include "render/model/ship_model.h"
#include "render/shader.h"
#include "render/texture.h"
#include "util/file.h"
#include "util/id.h"

Shader *shader;
Texture *texture;

#define MAX_ENTITY_RENDERERS 1000

HashMap GameRenderer_entity_renderers;

int GameRenderer_init() {
  const char *vertex_shader_source = load_file("res/shaders/shader.vert");

  if (vertex_shader_source == NULL) {
    printf("Failed to load vertex shader source\n");
    return 1;
  }

  const char *fragment_shader_source = load_file("res/shaders/shader.frag");

  if (fragment_shader_source == NULL) {
    printf("Failed to load fragment shader source\n");
    return 1;
  }

  shader = malloc(sizeof(Shader));
  *shader = Shader_new(vertex_shader_source, fragment_shader_source);

  if (shader == NULL) {
    printf("Failed to create shader\n");
    return 1;
  }

  printf("Shader created\n");

  texture = malloc(sizeof(Texture));
  *texture = Texture_load_from_image("res/img/texture.png");

  GameRenderer_entity_renderers = HashMap_new(MAX_ENTITY_RENDERERS, sizeof(Id));

  return 0;
}

void GameRenderer_render(RenderContext *render_context) {
  Texture_bind(texture);
  Shader_bind(*shader);

  M camera_transform = Camera_get_transform(&Game_camera);
  MStack_push(&render_context->matrix_stack, camera_transform);

  Iterator entities_iter = Iterator_new(&Game_entities);
  while (Iterator_has_next(&entities_iter)) {
    Entity *entity = Iterator_next(&entities_iter);

    EntityRenderer *entity_renderer =
        HashMap_get(GameRenderer_entity_renderers, &entity->id);

    if (entity_renderer == NULL) {
      entity_renderer = EntityRenderer_new_ptr(entity);
      HashMap_add(GameRenderer_entity_renderers, &entity->id, entity_renderer);
    }

    EntityRenderer_render(entity_renderer, render_context);
  }
}
