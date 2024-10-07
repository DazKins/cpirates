#include "game.h"

#include <stdio.h>

#include "../../game/entity/entity.h"
#include "../../render/model/model.h"
#include "../../render/shader.h"
#include "../../render/model/model_builder.h"
#include "../../render/model/ship_model.h"
#include "../../render/texture.h"
#include "../../util/file.h"

Model *model;
Shader *shader;
Texture *texture;

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

  ModelBuilder mb = ModelBuilder_new();

  ShipModel_build(&mb);

  model = ModelBuilder_build(&mb);

  texture = malloc(sizeof(Texture));
  *texture = Texture_load_from_image("res/img/texture.png");

  return 0;
}

void GameRenderer_render(RenderContext *render_context) {
  Texture_bind(texture);
  Shader_bind(*shader);

  Iterator entities_iter = Iterator_new(&Game_entities);
  while (Iterator_has_next(&entities_iter)) {
    Entity *entity = Iterator_next(&entities_iter);

  }

  RenderContext_render(render_context, model);
}
