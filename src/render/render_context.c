#include "render_context.h"

#include "render/shader.h"
#include "util/tim3.h"

RenderContext RenderContext_new() {
  RenderContext render_context;
  render_context.matrix_stack = MStack_new();
  return render_context;
}

void RenderContext_render(RenderContext *rc, Model *m) {
  M cur_m = MStack_peek(rc->matrix_stack);

  Shader_bind(m->shader);

  Shader_set_uniform_m(&m->shader, "mat", &cur_m);
  Shader_set_uniform_f(&m->shader, "time", get_time_s());

  Model_render(m);
}
