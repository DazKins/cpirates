#include "v.h"
#include <stdlib.h>

struct v {
  float x;
  float y;
  float z;
};

V *V_new(const float x, const float y, const float z) {
  V *v = malloc(sizeof(V));
  v->x = x;
  v->y = y;
  v->z = z;
  return v;
}

float V_getX(const V *v) { return v->x; }
float V_getY(const V *v) { return v->y; }
float V_getZ(const V *v) { return v->z; }

