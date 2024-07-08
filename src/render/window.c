#include "glad/glad.h"
#include "window.h"
#include <stdio.h>
#include <stdlib.h>

#include "../util/input.h"

static GLFWwindow *glfwWindow;
static void (*window_size_callback)(int, int);
static void (*cursor_pos_callback)(double, double);


void glfw_window_size_callback(GLFWwindow *window, int width, int height) {
  if (!window_size_callback) {
    return;
  }
  window_size_callback(width, height);
}

void Window_create(const int width, const int height, const char *title) {

  if (glfwInit() == GLFW_FALSE) {
    printf("Failed to initialize GLFW\n");
    exit(1);
  }

  printf("GLFW initialized\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

  if (!glfwWindow) {
    printf("Failed to create window\n");
    glfwTerminate();
    exit(1);
  }

  printf("Window created\n");

  glfwMakeContextCurrent(glfwWindow);

  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    exit(1);
  }

  if (glfwRawMouseMotionSupported()) {
    glfwSetInputMode(glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }

  glfwSetWindowSizeCallback(glfwWindow, glfw_window_size_callback);
  glfwSetKeyCallback(glfwWindow, glfw_key_callback);
  glfwSetCursorPosCallback(glfwWindow, glfw_cursor_pos_callback);
}

int Window_should_close() { return glfwWindowShouldClose(glfwWindow); }

void Window_poll_events() { glfwPollEvents(); }

void Window_swap_buffers() { glfwSwapBuffers(glfwWindow); }

void Window_hide_cursor() {
  glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window_set_window_size_callback(void (*callback)(int, int)) {
  window_size_callback = callback;
}
