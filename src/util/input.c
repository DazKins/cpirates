#include "input.h"

int keys_down[GLFW_KEY_LAST];

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action,
                       int mods) {
  if (action == GLFW_PRESS) {
    keys_down[key] = 1;
  } else if (action == GLFW_RELEASE) {
    keys_down[key] = 0;
  }
}

static V2 prev_mouse_pos;
static V2 mouse_pos;

static V2 mouse_delta;

void glfw_cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
  mouse_pos.x = xpos;
  mouse_pos.y = ypos;
}

V2 Input_get_mouse_pos() { return mouse_pos; };

int Input_is_key_down(int key) { return keys_down[key]; }

void Input_tick() {
  mouse_delta = V2_sub(&mouse_pos, &prev_mouse_pos);
  prev_mouse_pos = mouse_pos;
}

V2 Input_get_mouse_delta() { return mouse_delta; }
