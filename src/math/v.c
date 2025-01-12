#include "v.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "math/num.h"

const V V_0 = {0.0f, 0.0f, 0.0f};

const V2 V2_0 = {0.0f, 0.0f};

const V2 V2_00 = {0.0f, 0.0f};
const V2 V2_01 = {0.0f, 1.0f};
const V2 V2_10 = {1.0f, 0.0f};
const V2 V2_11 = {1.0f, 1.0f};

V V_new(float x, float y, float z) {
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

V V_add(V v0, V v1) { return V_new(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z); }

V V_mul(V v, float a) { return V_new(v.x * a, v.y * a, v.z * a); }

V V_set_x(V v, float x) {
  v.x = x;
  return v;
}

V V_set_y(V v, float y) {
  v.y = y;
  return v;
}

V V_set_z(V v, float z) {
  v.z = z;
  return v;
}

V V_neg(V v) { return V_new(-v.x, -v.y, -v.z); }

V V_norm(V v) {
  float mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  return V_new(v.x / mag, v.y / mag, v.z / mag);
}

int V_eq(V v0, V v1) { return v0.x == v1.x && v0.y == v1.y && v0.z == v1.z; }

V V_clamp(V v, float min, float max) {
  v.x = clamp(v.x, min, max);
  v.y = clamp(v.y, min, max);
  v.z = clamp(v.z, min, max);
  return v;
}

V V_wrap(V v, float min, float max) {
  v.x = wrap(v.x, min, max);
  v.y = wrap(v.y, min, max);
  v.z = wrap(v.z, min, max);
  return v;
}

V2 V2_sub(V2 a, V2 b) { return V2_new(a.x - b.x, a.y - b.y); }

char *V_to_string(V v) {
  char *str = malloc(64);
  sprintf(str, "V(%f, %f, %f)", v.x, v.y, v.z);
  return str;
}
