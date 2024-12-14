#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "render/model/model.h"
#include "render/m_stack.h"

typedef struct {
  MStack matrix_stack;
} RenderContext;

RenderContext RenderContext_new();

void RenderContext_render(RenderContext *rc, Model *m);

#endif // !RENDER_CONTEXT_H
