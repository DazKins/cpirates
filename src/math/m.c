#include "m.h"
#include <math.h>

M M_new(const size_t d) {
  M m;
  m.d = d;
  m.data = calloc(d * d, sizeof(float));
  return m;
}

M M_mul(const M a, const M b) {
  M c = M_new(a.d);
  for (size_t i = 0; i < a.d; i++) {
    for (size_t j = 0; j < a.d; j++) {
      for (size_t k = 0; k < a.d; k++) {
        c.data[i * a.d + j] += a.data[i * a.d + k] * b.data[k * a.d + j];
      }
    }
  }
  return c;
}

M M_I(const size_t d) {
  M m = M_new(d);
  for (size_t i = 0; i < d; i++) {
    m.data[i * d + i] = 1;
  }
  return m;
}

M M_Translate(V v) {
  M m = M_I(4);
  m.data[3 * 4 + 0] = v.x;
  m.data[3 * 4 + 1] = v.y;
  m.data[3 * 4 + 2] = v.z;
  return m;
}

M M_RotX(float a) {
  float cosA = cos(a);
  float sinA = sin(a);

  M m = M_I(4);
  m.data[1 * 4 + 1] = cosA;
  m.data[1 * 4 + 2] = sinA;
  m.data[2 * 4 + 1] = -sinA;
  m.data[2 * 4 + 2] = cosA;
  return m;
}

M M_RotY(float a) {
  float cosA = cos(a);
  float sinA = sin(a);

  M m = M_I(4);
  m.data[0 * 4 + 0] = cosA;
  m.data[0 * 4 + 2] = -sinA;
  m.data[2 * 4 + 0] = sinA;
  m.data[2 * 4 + 2] = cosA;
  return m;
}

M M_RotZ(float a) {
  float cosA = cos(a);
  float sinA = sin(a);

  M m = M_I(4);
  m.data[0 * 4 + 0] = cosA;
  m.data[0 * 4 + 1] = sinA;
  m.data[1 * 4 + 0] = -sinA;
  m.data[1 * 4 + 1] = cosA;
  return m;
}

M M_Scale(V v) {
  M m = M_I(4);
  m.data[0 * 4 + 0] = v.x;
  m.data[1 * 4 + 1] = v.y;
  m.data[2 * 4 + 2] = v.z;
  return m;
}

void M_free(M m) { free(m.data); }
