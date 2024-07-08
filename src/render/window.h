#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

void Window_create(const int width, const int height, const char *title);

void Window_set_window_size_callback(void (*callback)(int, int));

int Window_should_close();
void Window_poll_events();
void Window_swap_buffers();
void Window_hide_cursor();

#endif // !WINDOW_H
