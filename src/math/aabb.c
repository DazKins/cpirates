#include "aabb.h"

#include <stdio.h>
#include <stdlib.h>

AABB AABB_new(V min, V max) {
  AABB aabb;
  aabb.min = min;
  aabb.max = max;
  return aabb;
}

int AABB_contains(AABB aabb0, AABB aabb1) {
  if (aabb0.max.x < aabb1.min.x || aabb0.min.x > aabb1.max.x)
    return 0;
  if (aabb0.max.y < aabb1.min.y || aabb0.min.y > aabb1.max.y)
    return 0;
  if (aabb0.max.z < aabb1.min.z || aabb0.min.z > aabb1.max.z)
    return 0;
  return 1;
}

AABB AABB_translate(AABB aabb, V v) {
  aabb.min = V_add(aabb.min, v);
  aabb.max = V_add(aabb.max, v);
  return aabb;
}

const char *AABB_to_string(AABB aabb) {
  char *str = malloc(128);

  const char *min_str = V_to_string(aabb.min);
  const char *max_str = V_to_string(aabb.max);

  sprintf(str, "AABB(min: %s, max: %s)", min_str, max_str);
  return str;
}
