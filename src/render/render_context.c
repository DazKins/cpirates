#include "render_context.h"

#include "shader.h"

RenderContext RenderContext_new() {
  RenderContext render_context;
  render_context.matrix_stack = MStack_new();
  return render_context;
}

void RenderContext_render(const RenderContext *rc, const Model *m) {
  M cur_m = MStack_peek(rc->matrix_stack);
  Shader cur_shader = get_currently_bound_shader();

  Shader_set_uniform_m(&cur_shader, "mat", &cur_m);

  Model_render(m);
}
