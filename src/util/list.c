#include "list.h"
#include <stdlib.h>

void List_push(List *list, void *data) {
  _ListNode *list_node = malloc(sizeof(_ListNode));
  list_node->data = data;
  list_node->next = NULL;
  list_node->prev = list->end;

  if (list->head == NULL) {
    list->head = list_node;
    return;
  }

  list->end->next = list_node;
  list->end = list_node;
}

Iterator Iterator_new(List *list) {
  Iterator iterator;

  if (list == NULL) {
    iterator.current = NULL;
  }

  iterator.current = list->head;
  return iterator;
}

void *Iterator_next(Iterator *iterator) {
  if (iterator->current == NULL) {
    return NULL;
  }
  void *data = iterator->current->data;
  iterator->current = iterator->current->next;
  return data;
}

