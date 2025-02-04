#ifndef LIST_H
#define LIST_H

typedef struct _listNode {
  void *data;
  struct _listNode *next;
  struct _listNode *prev;
} _ListNode;

void _ListNode_free(_ListNode *node);

typedef struct list {
  _ListNode *head;
  _ListNode *end;
} List;

List List_new();

void List_push(List *list, void *data);
void List_free(List list);

typedef struct {
  _ListNode *current;
} Iterator;

Iterator Iterator_new(List *list);

int Iterator_has_next(Iterator *it);
void *Iterator_next(Iterator *it);
void Iterator_free(Iterator *it);

#endif // !LIST_H
