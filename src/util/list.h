#ifndef LIST_H
#define LIST_H

typedef struct _listNode {
  void *data;
  struct _listNode *next;
  struct _listNode *prev;
} _ListNode;

typedef struct list {
  void *data;
  _ListNode *head;
  _ListNode *end;
} List;

typedef struct {
  _ListNode *current;
} Iterator;

void List_push(List *list, void *data);

Iterator Iterator_new(List *list);
void *Iterator_next(Iterator *it);

#endif // !LIST_H
