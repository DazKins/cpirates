#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List List_new() {
  List list;
  return list;
}

void List_push(List *list, void *data) {
  _ListNode *list_node = malloc(sizeof(_ListNode));
  list_node->data = data;
  list_node->next = NULL;
  list_node->prev = list->end;

  if (list->head == NULL) {
    list->head = list_node;
    list->end = list_node;
    return;
  }

  list->end->next = list_node;
  list->end = list_node;
}

void _ListNode_free(_ListNode *list_node) {
  if (list_node == NULL) {
    return;
  }

  _ListNode_free(list_node->next);
  free(list_node->data);
  free(list_node);
}

void List_free(List list) { _ListNode_free(list.head); }

Iterator Iterator_new(List *list) {
  Iterator iterator;

  if (list == NULL) {
    iterator.current = NULL;
  }

  iterator.current = list->head;
  return iterator;
}

int Iterator_has_next(Iterator *iterator) { return iterator->current != NULL; }

void *Iterator_next(Iterator *iterator) {
  if (iterator->current == NULL) {
    return NULL;
  }
  void *data = iterator->current->data;
  iterator->current = iterator->current->next;
  return data;
}
