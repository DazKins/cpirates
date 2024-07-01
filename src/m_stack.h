#ifndef MAT_STACK_H
#define MAT_STACK_H

#include "m.h"

struct mStack;
typedef struct mStack MStack;

MStack *MStack_new();

void MStack_push(MStack *ms, const M *m);
const M *MStack_pop(MStack *ms);
const M *MStack_peek(MStack *ms);

#endif // !MAT_STACK_H
