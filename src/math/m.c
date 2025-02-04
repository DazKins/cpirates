#include "m.h"

#include <math.h>
#include <stdio.h>

M M_new() {
  M m = {0};
  return m;
}

M M_mul(const M a, const M b) {
  M c = M_new();

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      for (size_t k = 0; k < 4; k++) {
        c.data[j * 4 + i] += a.data[k * 4 + i] * b.data[j * 4 + k];
      }
    }
  }
  return c;
}

M M_I() {
  M m = M_new();

  m.data[0 * 4 + 0] = 1.0f;
  m.data[0 * 4 + 1] = 0.0f;
  m.data[0 * 4 + 2] = 0.0f;
  m.data[0 * 4 + 3] = 0.0f;

  m.data[1 * 4 + 0] = 0.0f;
  m.data[1 * 4 + 1] = 1.0f;
  m.data[1 * 4 + 2] = 0.0f;
  m.data[1 * 4 + 3] = 0.0f;

  m.data[2 * 4 + 0] = 0.0f;
  m.data[2 * 4 + 1] = 0.0f;
  m.data[2 * 4 + 2] = 1.0f;
  m.data[2 * 4 + 3] = 0.0f;

  m.data[3 * 4 + 0] = 0.0f;
  m.data[3 * 4 + 1] = 0.0f;
  m.data[3 * 4 + 2] = 0.0f;
  m.data[3 * 4 + 3] = 1.0f;

  return m;
}

M M_Translate(V v) {
  M m;

  m.data[0 * 4 + 0] = 1.0f;
  m.data[0 * 4 + 1] = 0.0f;
  m.data[0 * 4 + 2] = 0.0f;
  m.data[0 * 4 + 3] = 0.0f;

  m.data[1 * 4 + 0] = 0.0f;
  m.data[1 * 4 + 1] = 1.0f;
  m.data[1 * 4 + 2] = 0.0f;
  m.data[1 * 4 + 3] = 0.0f;

  m.data[2 * 4 + 0] = 0.0f;
  m.data[2 * 4 + 1] = 0.0f;
  m.data[2 * 4 + 2] = 1.0f;
  m.data[2 * 4 + 3] = 0.0f;

  m.data[3 * 4 + 0] = v.x;
  m.data[3 * 4 + 1] = v.y;
  m.data[3 * 4 + 2] = v.z;
  m.data[3 * 4 + 3] = 1.0f;

  return m;
}

M M_RotX(float a) {
  float cosA = cos(a);
  float sinA = sin(a);

  M m = M_new();

  m.data[0 * 4 + 0] = 1.0f;
  m.data[0 * 4 + 1] = 0.0f;
  m.data[0 * 4 + 2] = 0.0f;
  m.data[0 * 4 + 3] = 0.0f;

  m.data[1 * 4 + 0] = 0.0f;
  m.data[1 * 4 + 1] = cosA;
  m.data[1 * 4 + 2] = -sinA;
  m.data[1 * 4 + 3] = 0.0f;

  m.data[2 * 4 + 0] = 0.0f;
  m.data[2 * 4 + 1] = sinA;
  m.data[2 * 4 + 2] = cosA;
  m.data[2 * 4 + 3] = 0.0f;

  m.data[3 * 4 + 0] = 0.0f;
  m.data[3 * 4 + 1] = 0.0f;
  m.data[3 * 4 + 2] = 0.0f;
  m.data[3 * 4 + 3] = 1.0f;

  return m;
}

M M_RotY(float a) {
  float cosA = cos(a);
  float sinA = sin(a);

  M m = M_new();

  m.data[0 * 4 + 0] = cosA;
  m.data[0 * 4 + 1] = 0.0f;
  m.data[0 * 4 + 2] = sinA;
  m.data[0 * 4 + 3] = 0.0f;

  m.data[1 * 4 + 0] = 0.0f;
  m.data[1 * 4 + 1] = 1.0f;
  m.data[1 * 4 + 2] = 0.0f;
  m.data[1 * 4 + 3] = 0.0f;

  m.data[2 * 4 + 0] = -sinA;
  m.data[2 * 4 + 1] = 0.0f;
  m.data[2 * 4 + 2] = cosA;
  m.data[2 * 4 + 3] = 0.0f;

  m.data[3 * 4 + 0] = 0.0f;
  m.data[3 * 4 + 1] = 0.0f;
  m.data[3 * 4 + 2] = 0.0f;
  m.data[3 * 4 + 3] = 1.0f;

  return m;
}

M M_RotZ(float a) {
  float cosA = cos(a);
  float sinA = sin(a);

  M m = M_new();

  m.data[0 * 4 + 0] = cosA;
  m.data[0 * 4 + 1] = -sinA;
  m.data[0 * 4 + 2] = 0.0f;
  m.data[0 * 4 + 3] = 0.0f;

  m.data[1 * 4 + 0] = sinA;
  m.data[1 * 4 + 1] = cosA;
  m.data[1 * 4 + 2] = 0.0f;
  m.data[1 * 4 + 3] = 0.0f;

  m.data[2 * 4 + 0] = 0.0f;
  m.data[2 * 4 + 1] = 0.0f;
  m.data[2 * 4 + 2] = 1.0f;
  m.data[2 * 4 + 3] = 0.0f;

  m.data[3 * 4 + 0] = 0.0f;
  m.data[3 * 4 + 1] = 0.0f;
  m.data[3 * 4 + 2] = 0.0f;
  m.data[3 * 4 + 3] = 1.0f;

  return m;
}

M M_Scale(V v) {
  M m = M_new();

  m.data[0 * 4 + 0] = v.x;
  m.data[0 * 4 + 1] = 0.0f;
  m.data[0 * 4 + 2] = 0.0f;
  m.data[0 * 4 + 3] = 0.0f;

  m.data[1 * 4 + 0] = 0.0f;
  m.data[1 * 4 + 1] = v.y;
  m.data[1 * 4 + 2] = 0.0f;
  m.data[1 * 4 + 3] = 0.0f;

  m.data[2 * 4 + 0] = 0.0f;
  m.data[2 * 4 + 1] = 0.0f;
  m.data[2 * 4 + 2] = v.z;
  m.data[2 * 4 + 3] = 0.0f;

  m.data[3 * 4 + 0] = 0.0f;
  m.data[3 * 4 + 1] = 0.0f;
  m.data[3 * 4 + 2] = 0.0f;
  m.data[3 * 4 + 3] = 1.0f;

  return m;
}

M M_perspective(float fov, float aspect, float near, float far) {
  float q = tan(M_PI / 2.0f - fov / 2.0f);

  M m = M_new();

  m.data[0 * 4 + 0] = q / aspect;
  m.data[0 * 4 + 1] = 0.0f;
  m.data[0 * 4 + 2] = 0.0f;
  m.data[0 * 4 + 3] = 0.0f;

  m.data[1 * 4 + 0] = 0.0f;
  m.data[1 * 4 + 1] = q;
  m.data[1 * 4 + 2] = 0.0f;
  m.data[1 * 4 + 3] = 0.0f;

  m.data[2 * 4 + 0] = 0.0f;
  m.data[2 * 4 + 1] = 0.0f;
  m.data[2 * 4 + 2] = -(far + near) / (far - near);
  m.data[2 * 4 + 3] = -1;

  m.data[3 * 4 + 0] = 0.0f;
  m.data[3 * 4 + 1] = 0.0f;
  m.data[3 * 4 + 2] = -(2 * near * far) / (far - near);
  m.data[3 * 4 + 3] = 0.0f;

  return m;
}

void M_print(M m) {
  printf("[\n");
  for (size_t i = 0; i < 4; i++) {
    printf("  [");
    for (size_t j = 0; j < 4; j++) {
      printf("%f, ", m.data[j * 4 + i]);
    }
    printf("]\n");
  }
  printf("]\n");
}
