#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer_object.h"
#include "file.h"
#include "shader.h"
#include "vec.h"

GLFWwindow *window;
BufferObject *buffer_object;
Shader *shader;

int init() {
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

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
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

  shader = Shader_new(vertex_shader_source, fragment_shader_source);

  if (shader == NULL) {
    printf("Failed to create shader\n");
    return 1;
  }

  printf("Shader created\n");

  const V3 positions[] = {
      {0.5f, 0.5f, 0.0f},
      {0.5f, -0.5f, 0.0f},
      {-0.5f, -0.5f, 0.0f},
  };

  const unsigned int indices[] = {0, 1, 2};

  buffer_object = BufferObject_new(3, positions, 3, indices);

  return 0;
}

int main() {
  if (init() != 0) {
    return 1;
  }

  printf("Initialized\n");

  while (!glfwWindowShouldClose(window)) {
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);

    glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Shader_bind(shader);
    BufferObject_render(buffer_object);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
