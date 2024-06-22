#define GLFW_INCLUDE_GLCOREARB

#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "shader.h"
#include "file.h"

GLFWwindow *window;

int init() {
  if (glfwInit() == GLFW_FALSE) {
    printf("Failed to initialize GLFW\n");
    return 1;
  }

  printf("GLFW initialized\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

  if (!window) {
    printf("Failed to create window\n");
    glfwTerminate();
    return 1;
  }

  printf("Window created\n");

  glfwMakeContextCurrent(window);

  const char * vertex_shader_source = load_file("shaders/shader.vert");

  if (vertex_shader_source == NULL) {
    printf("Failed to load vertex shader source\n");
    return 1;
  }

  const char * fragment_shader_source = load_file("shaders/shader.frag");

  if (fragment_shader_source == NULL) {
    printf("Failed to load fragment shader source\n");
    return 1;
  }

  Shader *shader = Shader_new(vertex_shader_source, fragment_shader_source);

  if (shader == NULL) {
    printf("Failed to create shader\n");
    return 1;
  }

  printf("Shader created\n");

  return 0;
}

int main() {
  if (init() != 0) {
    return 1;
  }

  printf("Initialized\n");

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
