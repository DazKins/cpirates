#include "input.h"

int keys_down[GLFW_KEY_LAST];

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    keys_down[key] = 1;
  } else if (action == GLFW_RELEASE) {
    keys_down[key] = 0;
  }
}

int Input_is_key_down(int key) {
  return keys_down[key];
}

