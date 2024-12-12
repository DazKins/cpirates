#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

typedef struct {
  uint64_t _capacity;
  size_t _key_size;
  void *_data;
} HashMap;

HashMap HashMap_new(uint64_t capacity, size_t key_size);

void HashMap_add(HashMap h, void *key, void *value);
void *HashMap_get(HashMap h, void *key);
void HashMap_remove(HashMap h, void *key);

#endif // !MAP_H
