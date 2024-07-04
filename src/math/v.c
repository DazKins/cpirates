#include "v.h"

V V_new(const float x, const float y, const float z) {
  V v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

