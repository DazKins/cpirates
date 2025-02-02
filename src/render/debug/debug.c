#include "debug.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "game/game.h"
#include "render/shader.h"
#include "util/file.h"

int _init = 0;
Shader *_debug_shader;

GLuint _point_vbo;
GLuint _point_vao;

void debug_init() {
  if (_init)
    return;

  const char *debug_vertex_shader_source = load_file("res/shaders/shader.vert");

  if (debug_vertex_shader_source == NULL) {
    printf("Failed to load debug vertex shader source\n");
  }

  const char *debug_fragment_shader_source =
      load_file("res/shaders/shader.frag");

  if (debug_fragment_shader_source == NULL) {
    printf("failed to load debug fragment shader source\n");
  }

  _debug_shader = malloc(sizeof(Shader));
  *_debug_shader =
      Shader_new(debug_vertex_shader_source, debug_fragment_shader_source);

  glGenVertexArrays(1, &_point_vao);
  glGenBuffers(1, &_point_vbo);

  glBindVertexArray(_point_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _point_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  _init = 1;
}

void DebugRender_point(V v) {
  debug_init();

  Shader_bind(*_debug_shader);

  M m = Camera_get_transform(&Game_camera);

  V look = V_norm(V_sub(Game_camera.pos, v));
  V world_up = V_new(0.0f, 1.0f, 0.0f);
  V right = V_norm(V_cross(world_up, look));
  V up = V_norm(V_cross(look, right));

  Shader_set_uniform_v(_debug_shader, "debugColor", V_new(1.0f, 1.0f, 1.0f));
  Shader_set_uniform_m(_debug_shader, "mat", &m);

  float half_size = 0.2f;

  V v1 = V_sub(V_sub(v, V_mul(right, half_size)), V_mul(up, half_size));
  V v2 = V_sub(V_add(v, V_mul(right, half_size)), V_mul(up, half_size));
  V v3 = V_add(V_sub(v, V_mul(right, half_size)), V_mul(up, half_size));
  V v4 = V_add(V_add(v, V_mul(right, half_size)), V_mul(up, half_size));

  float quad_vertices[] = {v1.x, v1.y, v1.z, v2.x, v2.y, v2.z,
                           v3.x, v3.y, v3.z, v4.x, v4.y, v4.z};

  glDisable(GL_DEPTH_TEST);

  glBindBuffer(GL_ARRAY_BUFFER, _point_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices,
               GL_DYNAMIC_DRAW);

  glBindVertexArray(_point_vao);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray(0);

  glEnable(GL_DEPTH_TEST);

  Shader_unbind();
}
