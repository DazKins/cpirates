#include "aabb.h"

AABB AABB_new(V min, V max) {
  AABB aabb;
  aabb.min = min;
  aabb.max = max;
  return aabb;
}

int AABB_contains(AABB aabb0, AABB aabb1) {
  if (aabb0.max.x < aabb0.min.x || aabb0.min.x > aabb0.max.x)
    return 0;
  if (aabb0.max.y < aabb0.min.y || aabb0.min.y > aabb0.max.y)
    return 0;
  if (aabb0.max.z < aabb0.min.z || aabb0.min.z > aabb0.max.z)
    return 0;
  return 1;
}

AABB AABB_translate(AABB aabb, V v) {
  aabb.min = V_add(aabb.min, v);
  aabb.max = V_add(aabb.max, v);
  return aabb;
}
