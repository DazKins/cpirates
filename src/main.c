#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "math/m.h"
#include "render/buffer_object.h"
#include "util/file.h"
#include "util/tim3.h"
#include "render/m_stack.h"
#include "render/shader.h"
#include "math/v.h"

GLFWwindow *window;
BufferObject *buffer_object;
Shader *shader;
MStack *mStack;

int init() {
  time_init();

  if (glfwInit() == GLFW_FALSE) {
    printf("Failed to initialize GLFW\n");
    return 1;
  }

  printf("GLFW initialized\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

  if (!window) {
    printf("Failed to create window\n");
    glfwTerminate();
    return 1;
  }

  printf("Window created\n");

  glfwMakeContextCurrent(window);

  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return 1;
  }

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

  const unsigned int indices[] = {0, 1, 2};

  buffer_object = malloc(sizeof(BufferObject));
  *buffer_object = BufferObject_new(3, positions, 3, indices);

  mStack = malloc(sizeof(MStack));
  *mStack = MStack_new();

  return 0;
}

float t = 0.0f;

void tick() { t += 0.01f; }

void render() {
  MStack_load_identity(mStack);

  int window_width, window_height;
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);

  MStack_push(mStack, M_Scale(V_new((float)window_height / (float)window_width,
                                    1.0f, 1.0f)));

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  MStack_push(mStack, M_RotX(t));
  MStack_push(mStack, M_RotY(t));
  MStack_push(mStack, M_RotZ(t));

  Shader_bind(*shader);

  Shader_set_uniform_m(*shader, "mvp", MStack_peek(*mStack));

  BufferObject_render(buffer_object);

  glfwSwapBuffers(window);
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

  while (!glfwWindowShouldClose(window)) {
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
