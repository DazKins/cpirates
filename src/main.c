#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "math/m.h"
#include "render/model.h"
#include "render/camera.h"
#include "util/file.h"
#include "util/input.h"
#include "util/keys.h"
#include "util/tim3.h"
#include "render/m_stack.h"
#include "render/shader.h"
#include "render/window.h"
#include "math/v.h"

Model *model;
Shader *shader;
MStack *m_stack;
Camera *camera;

void window_size_callback(int width, int height) {
  printf("Window resized to %dx%d\n", width, height);

  camera->aspect_ratio = (float)width / height;
  glViewport(0, 0, width, height);
}

int init() {
  time_init();

  if (glfwInit() == GLFW_FALSE) {
    printf("Failed to initialize GLFW\n");
    return 1;
  }

  printf("GLFW initialized\n");

  Window_create(1280, 720, "Hello World");

  printf("Window created\n");

  Window_set_window_size_callback(window_size_callback);
  Window_hide_cursor();

  const char *vertex_shader_source = load_file("shaders/shader.vert");

  if (vertex_shader_source == NULL) {
    printf("Failed to load vertex shader source\n");
    return 1;
  }

  const char *fragment_shader_source = load_file("shaders/shader.frag");

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

  V *positions = malloc(sizeof(V) * 3);

  positions[0] = V_new(0.5f, 0.5f, 0.0f);
  positions[1] = V_new(0.5f, -0.5f, 0.0f);
  positions[2] = V_new(-0.5f, -0.5f, 0.0f);
  positions[3] = V_new(-0.5f, 0.5f, 0.0f);

  const unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  model = malloc(sizeof(Model));
  *model = Model_new(4, positions, 6, indices);

  m_stack = malloc(sizeof(MStack));
  *m_stack = MStack_new();

  camera = malloc(sizeof(Camera));
  *camera = Camera_new(1280.0f / 720.0f, M_PI / 2.0f, 0.01f, 100.0f);

  return 0;
}

int should_close = 0;

void tick() {
  Input_tick();

  Camera_process_input(camera);

  if (Input_is_key_down(KEY_ESCAPE)) {
    should_close = 1;
  }
}

void render() {
  MStack_load_identity(m_stack);

  M camera_transform = Camera_get_transform(camera);
  MStack_push(m_stack, camera_transform);

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  Shader_bind(*shader);

  Shader_set_uniform_m(*shader, "mvp", MStack_peek(*m_stack));

  Model_render(model);

  Window_swap_buffers();
}

int main() {
  if (init() != 0) {
    return 1;
  }

  printf("Initialized\n");

  long last_time = get_time_ns();

  long ns_per_tick = 1e9 / 160;
  long tick_delta_cum = 0;

  long frame_count = 0;
  long tick_count = 0;
  long last_log_time = get_time_ns();
  long ns_per_log = 5e9;
  long s_per_log = ns_per_log / 1e9;

  while (!Window_should_close() && !should_close) {
    long current_frame_time = get_time_ns();
    long delta_ns = current_frame_time - last_time;
    last_time = current_frame_time;

    tick_delta_cum += delta_ns;
    while (tick_delta_cum >= ns_per_tick) {
      tick_count++;
      tick();
      tick_delta_cum -= ns_per_tick;
    }

    frame_count++;
    render();

    if (current_frame_time - last_log_time > ns_per_log) {
      printf("FPS: %ld, UPS: %ld\n", frame_count / s_per_log,
             tick_count / s_per_log);
      frame_count = 0;
      tick_count = 0;
      last_log_time = current_frame_time;
    }

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
