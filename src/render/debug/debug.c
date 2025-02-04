#include "debug.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "game/game.h"
#include "math/obb.h"
#include "render/shader.h"
#include "util/file.h"

int _init = 0;
Shader *_debug_shader;

GLuint _debug_vbo;
GLuint _debug_vao;

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

  glGenVertexArrays(1, &_debug_vao);
  glGenBuffers(1, &_debug_vbo);

  glBindVertexArray(_debug_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _debug_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  _init = 1;
}

void DebugRender_point(V v, float size) {
  debug_init();

  Shader_bind(*_debug_shader);

  M m = Camera_get_transform(&Game_camera);

  V look = V_norm(V_sub(Game_camera.pos, v));
  V world_up = V_new(0.0f, 1.0f, 0.0f);
  V right = V_norm(V_cross(world_up, look));
  V up = V_norm(V_cross(look, right));

  Shader_set_uniform_v(_debug_shader, "debugColor", V_new(1.0f, 1.0f, 1.0f));
  Shader_set_uniform_m(_debug_shader, "mat", &m);

  float half_size = size / 2.0f;

  V v1 = V_sub(V_sub(v, V_mul(right, half_size)), V_mul(up, half_size));
  V v2 = V_sub(V_add(v, V_mul(right, half_size)), V_mul(up, half_size));
  V v3 = V_add(V_sub(v, V_mul(right, half_size)), V_mul(up, half_size));
  V v4 = V_add(V_add(v, V_mul(right, half_size)), V_mul(up, half_size));

  float quad_vertices[] = {v1.x, v1.y, v1.z, v2.x, v2.y, v2.z,
                           v3.x, v3.y, v3.z, v4.x, v4.y, v4.z};

  glDisable(GL_DEPTH_TEST);

  glBindBuffer(GL_ARRAY_BUFFER, _debug_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices,
               GL_DYNAMIC_DRAW);

  glBindVertexArray(_debug_vao);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray(0);

  glEnable(GL_DEPTH_TEST);

  Shader_unbind();
}

void DebugRender_obb(OBB obb) {
  debug_init();
  
  Shader_bind(*_debug_shader);

  // Use the camera transformation matrix for the scene.
  M m = Camera_get_transform(&Game_camera);
  Shader_set_uniform_m(_debug_shader, "mat", &m);

  // Set the debug color for the OBB (e.g., red).
  Shader_set_uniform_v(_debug_shader, "debugColor", V_new(1.0f, 0.0f, 0.0f));

  // Assuming obb.axis[0] is right, obb.axis[1] is up, and obb.axis[2] is forward:
  V right   = obb.axis[0];
  V up      = obb.axis[1];
  V forward = obb.axis[2];

  // Compute centers for the bottom and top faces.
  V bottomCenter = V_sub(obb.center, V_mul(up, obb.half_extents.y));
  V topCenter    = V_add(obb.center, V_mul(up, obb.half_extents.y));

  // Compute bottom face corners.
  // v0 = bottomCenter - right*half_extents.x - forward*half_extents.z
  V v0 = V_sub(V_sub(bottomCenter, V_mul(right, obb.half_extents.x)),
              V_mul(forward, obb.half_extents.z));
  // v1 = bottomCenter + right*half_extents.x - forward*half_extents.z
  V v1 = V_add(V_sub(bottomCenter, V_mul(forward, obb.half_extents.z)),
              V_mul(right, obb.half_extents.x));
  // v2 = bottomCenter + right*half_extents.x + forward*half_extents.z
  V v2 = V_add(V_add(bottomCenter, V_mul(right, obb.half_extents.x)),
              V_mul(forward, obb.half_extents.z));
  // v3 = bottomCenter - right*half_extents.x + forward*half_extents.z
  V v3 = V_add(V_sub(bottomCenter, V_mul(right, obb.half_extents.x)),
              V_mul(forward, obb.half_extents.z));

  // Compute top face corners.
  // v4 = topCenter - right*half_extents.x - forward*half_extents.z
  V v4 = V_sub(V_sub(topCenter, V_mul(right, obb.half_extents.x)),
              V_mul(forward, obb.half_extents.z));
  // v5 = topCenter + right*half_extents.x - forward*half_extents.z
  V v5 = V_add(V_sub(topCenter, V_mul(forward, obb.half_extents.z)),
              V_mul(right, obb.half_extents.x));
  // v6 = topCenter + right*half_extents.x + forward*half_extents.z
  V v6 = V_add(V_add(topCenter, V_mul(right, obb.half_extents.x)),
              V_mul(forward, obb.half_extents.z));
  // v7 = topCenter - right*half_extents.x + forward*half_extents.z
  V v7 = V_add(V_sub(topCenter, V_mul(right, obb.half_extents.x)),
              V_mul(forward, obb.half_extents.z));

  float line_vertices[] = {
      // Bottom face edges
      v0.x, v0.y, v0.z, v1.x, v1.y, v1.z,
      v1.x, v1.y, v1.z, v2.x, v2.y, v2.z,
      v2.x, v2.y, v2.z, v3.x, v3.y, v3.z,
      v3.x, v3.y, v3.z, v0.x, v0.y, v0.z,

      // Top face edges
      v4.x, v4.y, v4.z, v5.x, v5.y, v5.z,
      v5.x, v5.y, v5.z, v6.x, v6.y, v6.z,
      v6.x, v6.y, v6.z, v7.x, v7.y, v7.z,
      v7.x, v7.y, v7.z, v4.x, v4.y, v4.z,

      // Vertical edges connecting bottom and top faces
      v0.x, v0.y, v0.z, v4.x, v4.y, v4.z,
      v1.x, v1.y, v1.z, v5.x, v5.y, v5.z,
      v2.x, v2.y, v2.z, v6.x, v6.y, v6.z,
      v3.x, v3.y, v3.z, v7.x, v7.y, v7.z
  };

  glDisable(GL_DEPTH_TEST);

  glBindBuffer(GL_ARRAY_BUFFER, _debug_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_DYNAMIC_DRAW);

  glBindVertexArray(_debug_vao);
  // There are 12 line segments (24 vertices) to draw.
  glDrawArrays(GL_LINES, 0, 24);
  glBindVertexArray(0);

  glEnable(GL_DEPTH_TEST);

  Shader_unbind();
}
