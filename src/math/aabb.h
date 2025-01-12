#include "v.h"
#ifndef AABB_H
#define AABB_H

typedef struct {
  V min;
  V max;
} AABB;

AABB AABB_new(V min, V max);

int AABB_contains(AABB aabb0, AABB aabb1);
AABB AABB_translate(AABB aabb, V v);

#endif // !AABB_H