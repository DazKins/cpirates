#ifndef MAT_STACK_H
#define MAT_STACK_H

#include "math/m.h"

struct mStack_node;
typedef struct mStack_node MStack_node;

typedef struct {
  MStack_node *head;
} MStack;

MStack MStack_new();

void MStack_push(MStack *ms, const M m);
void MStack_pop(MStack *ms);
const M MStack_peek(MStack ms);
void MStack_load_identity(MStack *ms);

#endif // !MAT_STACK_H
