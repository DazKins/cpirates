#include "game_renderer.h"

#include <stdio.h>

#include "game/entity/entity.h"
#include "render/game/entity/entity_renderer.h"
#include "render/model/model.h"
#include "render/model/model_builder.h"
#include "render/model/model_ship.h"
#include "render/model/model_sea.h"
#include "render/shader.h"
#include "render/texture.h"
#include "util/file.h"
#include "util/id.h"
#include "util/tim3.h"

Shader *shader;
Texture *texture;

Shader* sea_shader;

#define MAX_ENTITY_RENDERERS 1000

HashMap GameRenderer_entity_renderers;

Model *model_sea;

int GameRenderer_init() {
  const char *vertex_shader_source = load_file("res/shaders/shader.vert");

  if (vertex_shader_source == NULL) {
    printf("Failed to load vertex shader source\n");
    return 1;
  }

  const char *fragment_shader_source = load_file("res/shaders/shader.frag");

  if (fragment_shader_source == NULL) {
    printf("failed to load fragment shader source\n");
    return 1;
  }

  shader = malloc(sizeof(Shader));
  *shader = Shader_new(vertex_shader_source, fragment_shader_source);

  if (shader == NULL) {
    printf("failed to create shader\n");
    return 1;
  }
  const char *sea_vertex_shader_source = load_file("res/shaders/sea_shader.vert");

  if (vertex_shader_source == NULL) {
    printf("failed to load sea vertex shader source\n");
    return 1;
  }

  const char *sea_fragment_shader_source = load_file("res/shaders/sea_shader.frag");

  if (fragment_shader_source == NULL) {
    printf("failed to load sea fragment shader source\n");
    return 1;
  }

  sea_shader = malloc(sizeof(Shader));
  *sea_shader = Shader_new(sea_vertex_shader_source, sea_fragment_shader_source);

  if (sea_shader == NULL) {
    printf("failed to create sea shader\n");
    return 1;
  }

  printf("Shaders created\n");

  texture = malloc(sizeof(Texture));
  *texture = Texture_load_from_image("res/img/texture.png");

  GameRenderer_entity_renderers = HashMap_new(MAX_ENTITY_RENDERERS, sizeof(Id));

  ModelBuilder sea_model_builder = ModelBuilder_new();
  ModelSea_build(&sea_model_builder);
  model_sea = ModelBuilder_build(&sea_model_builder);

  return 0;
}

void GameRenderer_render(RenderContext *render_context) {
  Texture_bind(texture);
  Shader_bind(*shader);

  M camera_transform = Camera_get_transform(&Game_camera);
  MStack_push(&render_context->matrix_stack, camera_transform);

  List entities = Game_get_entities();
  Iterator entities_iter = Iterator_new(&entities);
  while (Iterator_has_next(&entities_iter)) {
    Entity *entity = Iterator_next(&entities_iter);

    EntityRenderer *entity_renderer =
        HashMap_get(GameRenderer_entity_renderers, &entity->id);

    if (entity_renderer == NULL) {
      entity_renderer = EntityRenderer_new_ptr(entity);
      if (entity_renderer != NULL) {
        HashMap_add(GameRenderer_entity_renderers, &entity->id,
                    entity_renderer);
      }
    }

    if (entity_renderer != NULL) {
      EntityRenderer_render(entity_renderer, render_context);
    }
  }

  Shader_bind(*sea_shader);
  Shader_set_uniform_f(sea_shader, "time", get_time_s());

  RenderContext_render(render_context, model_sea);
}
