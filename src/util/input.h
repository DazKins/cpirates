#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "../math/v.h"

int Input_is_key_down(int key);
V2 Input_get_mouse_pos();
V2 Input_get_mouse_delta();

void Input_tick();

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void glfw_cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);

#endif // !INPUT_H
