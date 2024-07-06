#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

int Input_is_key_down(int key);

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

#endif // !INPUT_H
