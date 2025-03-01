#include "m_stack.h"

#include <stdio.h>

struct mStack_node {
  M m;
  struct mStack_node *next;
};

MStack MStack_new() {
  MStack_node *head = malloc(sizeof(MStack_node));
  head->m = M_I(4);
  head->next = NULL;

  MStack ms;
  ms.head = head;
  return ms;
}

void MStack_push(MStack *ms, const M m) {
  M cur = ms->head->m;
  M nm = M_mul(cur, m);

  MStack_node *new_head = malloc(sizeof(MStack_node));
  new_head->m = nm;
  new_head->next = ms->head;
  ms->head = new_head;
}

void MStack_pop(MStack *ms) {
  MStack_node *old_head = ms->head;
  const M m = old_head->m;

  ms->head = old_head->next;

  free(old_head);
}

const M MStack_peek(MStack ms) { return ms.head->m; }

void MStack_node_free(MStack_node *node) {
  if (node->next != NULL) {
    MStack_node_free(node->next);
  }
  free(node);
}

void MStack_load_identity(MStack *ms) {
  if (ms->head->next != NULL) {
    MStack_node_free(ms->head->next);
  }
  ms->head->m = M_I(4);
  ms->head->next = NULL;
}
