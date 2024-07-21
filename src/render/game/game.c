#include "game.h"

#include <stdio.h>

#include "../../render/model/model.h"
#include "../../render/shader.h"
#include "../../render/model/model_builder.h"
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

  ModelBuilder_set_position(&mb, V_new(0.5f, 0.5f, 0.0f));
  ModelBuilder_set_tex_coord(&mb, V2_new(1.0f, 1.0f));
  ModelBuilder_push_vertex(&mb);

  ModelBuilder_set_position(&mb, V_new(0.5f, -0.5f, 0.0f));
  ModelBuilder_set_tex_coord(&mb, V2_new(1.0f, 0.0f));
  ModelBuilder_push_vertex(&mb);

  ModelBuilder_set_position(&mb, V_new(-0.5f, -0.5f, 0.0f));
  ModelBuilder_set_tex_coord(&mb, V2_new(0.0f, 0.0f));
  ModelBuilder_push_vertex(&mb);

  ModelBuilder_set_position(&mb, V_new(-0.5f, 0.5f, 0.0f));
  ModelBuilder_set_tex_coord(&mb, V2_new(0.0f, 1.0f));
  ModelBuilder_push_vertex(&mb);

  ModelBuilder_push_index(&mb, 0);
  ModelBuilder_push_index(&mb, 1);
  ModelBuilder_push_index(&mb, 2);
  ModelBuilder_push_index(&mb, 2);
  ModelBuilder_push_index(&mb, 3);
  ModelBuilder_push_index(&mb, 0);

  model = ModelBuilder_build(&mb);

  texture = malloc(sizeof(Texture));
  *texture = Texture_load_from_image("res/img/texture.png");

  return 0;
}

void GameRenderer_render(RenderContext *render_context) {
  Texture_bind(texture);
  Shader_bind(*shader);

  RenderContext_render(render_context, model);
}
