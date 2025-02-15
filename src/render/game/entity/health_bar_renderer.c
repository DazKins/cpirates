#include "health_bar_renderer.h"
#include "game/entity/component/component_health.h"
#include "game/entity/component/component_position.h"
#include "game/game.h"
#include "util/file.h"

HealthBarRenderer HealthBarRenderer_new() {
  HealthBarRenderer renderer;

  // Load shaders
  const char *vertex_shader_source = load_file("res/shaders/health_bar.vert");
  const char *fragment_shader_source = load_file("res/shaders/health_bar.frag");
  renderer.shader = Shader_new(vertex_shader_source, fragment_shader_source);

  // Create a simple quad for the health bar
  float vertices[] = {
      -0.5f, 0.0f, 0.0f, // left
      0.5f,  0.0f, 0.0f, // right
      -0.5f, 1.0f, 0.0f, // top left
      0.5f,  1.0f, 0.0f  // top right
  };

  glGenVertexArrays(1, &renderer.vao);
  glGenBuffers(1, &renderer.vbo);

  glBindVertexArray(renderer.vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return renderer;
}

void HealthBarRenderer_render(HealthBarRenderer *renderer, Entity *entity,
                              RenderContext *render_context) {
  // Only render health bars for entities with both health and position
  // components
  ComponentHealth *health =
      (ComponentHealth *)Entity_get_component(entity, ComponentTypeHealth);
  ComponentPosition *position =
      (ComponentPosition *)Entity_get_component(entity, ComponentTypePosition);

  if (!health || !position) {
    return;
  }

  float health_percent = (float)ComponentHealth_get_health(health) /
                         (float)ComponentHealth_get_max_health(health);

  Shader_bind(renderer->shader);

  // Set uniforms
  M transform = Camera_get_transform(&Game_camera);
  Shader_set_uniform_m(&renderer->shader, "mat", &transform);
  Shader_set_uniform_v(&renderer->shader, "position", position->pos);
  Shader_set_uniform_v(&renderer->shader, "camera_pos", Game_camera.pos);
  Shader_set_uniform_f(&renderer->shader, "width", 1.0f);
  Shader_set_uniform_f(&renderer->shader, "health_percent", health_percent);

  // Enable alpha blending for health bars
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Render the health bar
  glBindVertexArray(renderer->vao);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);

  glDisable(GL_BLEND);

  Shader_unbind();
}