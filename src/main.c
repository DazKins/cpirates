#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "math/m.h"
#include "render/buffer_object.h"
#include "util/file.h"
#include "util/input.h"
#include "util/keys.h"
#include "util/tim3.h"
#include "render/m_stack.h"
#include "render/shader.h"
#include "render/window.h"
#include "math/v.h"

BufferObject *buffer_object;
Shader *shader;
MStack *m_stack;

M *perspective;

void window_size_callback(int width, int height) {
  printf("Window resized to %dx%d\n", width, height);

  *perspective = M_perspective(M_PI_2, (float)width / height, 0.1f, 100.0f);
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

  buffer_object = malloc(sizeof(BufferObject));
  *buffer_object = BufferObject_new(4, positions, 6, indices);

  m_stack = malloc(sizeof(MStack));
  *m_stack = MStack_new();

  perspective = malloc(sizeof(M));
  *perspective = M_perspective(M_PI_2, 1280.0f / 720.0f, 0.01f, 100.0f);

  return 0;
}

float x = 0.0f;
float y = 0.0f;
float z = 0.0f;

void tick() {
  if (Input_is_key_down(KEY_W)) {
    z -= 0.01f;
  }

  if (Input_is_key_down(KEY_S)) {
    z += 0.01f;
  }

  if (Input_is_key_down(KEY_A)) {
    x -= 0.01f;
  }

  if (Input_is_key_down(KEY_D)) {
    x += 0.01f;
  }
}

void render() {
  MStack_load_identity(m_stack);

  MStack_push(m_stack, *perspective);

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  MStack_push(m_stack, M_Translate(V_new(-x, 0.0f, -z)));

  Shader_bind(*shader);

  Shader_set_uniform_m(*shader, "mvp", MStack_peek(*m_stack));

  BufferObject_render(buffer_object);

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

  while (!Window_should_close()) {
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
