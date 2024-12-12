#include "map.h"
#include "hash.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  void *key;
  void *value;
  int is_tombstone;
} MapEntry;

HashMap HashMap_new(uint64_t capacity, size_t key_size) {
  MapEntry *data = calloc(capacity, sizeof(MapEntry));

  return (HashMap){._capacity = capacity, ._key_size = key_size, ._data = data};
}

void HashMap_tmp_check(HashMap h) {
  int index = 0;

  while (index < h._capacity) {
    MapEntry *entry = h._data + index * sizeof(MapEntry);
    // printf("%d: entry: %p\n", index, entry);
    printf("%d: data key: %p\n", index, entry->key);
    index++;
  }
}

void HashMap_add(HashMap h, void *key, void *value) {
  uint64_t index = hash(key) % h._capacity;
  MapEntry *entry = h._data + index * sizeof(MapEntry);

  do {
    if (!entry->key) {
      entry->key = malloc(h._key_size);
      memcpy(entry->key, key, h._key_size);
      entry->value = value;
      entry->is_tombstone = 0;

      return;
    }
    index = (index + 1) % h._capacity;
    entry = h._data + index * sizeof(MapEntry);
  } while (entry->key);
}

void *HashMap_get(HashMap h, void *key) {
  uint64_t index = hash(key) % h._capacity;
  uint64_t start_index = index;

  while (1) {
    MapEntry *entry = h._data + index * sizeof(MapEntry);

    if (entry->is_tombstone == 0) {
      if (entry->key != NULL) {
        if (memcmp(entry->key, key, h._key_size) == 0) {
          return entry->value;
        }
      } else {
        break;
      }
    }

    index = (index + 1) % h._capacity;

    if (index == start_index)
      break;
  }

  return NULL;
}

void HashMap_remove(HashMap h, void *key) {
  uint64_t index = hash(key) % h._capacity;
  MapEntry *entry = h._data + index * sizeof(MapEntry);
  do {
    if (entry->key && memcmp(entry->key, key, h._key_size) == 0) {
      free(entry->key);
      entry->key = NULL;
      entry->is_tombstone = 1;
      return;
    }
    index = (index + 1) % h._capacity;
    entry = h._data + index * sizeof(MapEntry);
  } while (entry->key);
}
