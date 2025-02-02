#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "math/m.h"
#include "render/game/game_renderer.h"
#include "render/render_context.h"
#include "render/window.h"
#include "util/id.h"
#include "util/input.h"
#include "util/keys.h"
#include "util/tim3.h"

RenderContext *render_context;

void window_size_callback(int width, int height) {
  printf("Window resized to %dx%d\n", width, height);

  Game_camera.aspect_ratio = (float)width / height;
  glViewport(0, 0, width, height);
}

int init() {
#ifndef RELEASE
  printf("Starting in debug mode...\n");
#endif

  time_init();

  Window_create(1280, 720, "cpirates");

  Window_set_window_size_callback(window_size_callback);
  Window_hide_cursor();

  if (Shader_init() != 0) {
    return 1;
  }

  if (Game_init() != 0) {
    return 1;
  }

  if (GameRenderer_init() != 0) {
    return 1;
  }

  render_context = malloc(sizeof(RenderContext));
  *render_context = RenderContext_new();

  glEnable(GL_DEPTH_TEST);

  return 0;
}

int should_close = 0;

void tick() {
  Input_tick();

  Game_tick();

  if (Input_is_key_down(KEY_ESCAPE)) {
    should_close = 1;
  }
}

void render() {
  MStack_load_identity(&render_context->matrix_stack);

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GameRenderer_render(render_context);

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

  while (!Window_should_close() && !should_close) {
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
