#include "m_stack.h"

typedef struct mStack_node {
  const M *m;
  struct mStack_node *next;
} MStack_node;

struct mStack {
  MStack_node *head;
};

MStack *MStack_new() {
  MStack_node *head = malloc(sizeof(MStack_node));
  head->m = M_I(4);
  head->next = NULL;

  MStack *ms = malloc(sizeof(MStack));
  ms->head = head;
  return ms;
}

void MStack_push(MStack *ms, const M *m) {
  const M *cur = ms->head->m;
  const M *nm = M_mul(cur, m);

  MStack_node *new_head = malloc(sizeof(MStack_node));
  new_head->m = nm;
  new_head->next = ms->head;
  ms->head = new_head;
}

const M *MStack_pop(MStack *ms) {
  MStack_node *old_head = ms->head;
  const M *m = old_head->m;

  ms->head = old_head->next;

  free(old_head);

  return m;
}

const M *MStack_peek(MStack *ms) { return ms->head->m; }
