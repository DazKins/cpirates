#include "hash.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

uint64_t hash(const void *v) {
  uint64_t hash = FNV_OFFSET;
  for (const char *p = v; *p; p++) {
    hash ^= (uint64_t)(*p);
    hash *= FNV_PRIME;
  }
  return hash;
}
