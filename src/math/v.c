#include "v.h"

V V_new(const float x, const float y, const float z) {
  V v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

V2 V2_new(const float x, const float y) {
  V2 v;
  v.x = x;
  v.y = y;
  return v;
}

V V_neg(const V *v) {
  return V_new(-v->x, -v->y, -v->z);
}

V2 V2_sub(const V2 *a, const V2 *b) {
  return V2_new(a->x - b->x, a->y - b->y);
}
