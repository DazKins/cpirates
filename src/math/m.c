#include "m.h"

#include <math.h>
#include <stdio.h>

M M_new(const size_t d) {
  M m;
  m.d = d;
  m.data = calloc(d * d, sizeof(float));
  return m;
}

M M_mul(const M a, const M b) {
  M c;

  c.d = a.d;
  c.data = malloc(c.d * c.d * sizeof(float));

  for (size_t i = 0; i < a.d; i++) {
    for (size_t j = 0; j < a.d; j++) {
      for (size_t k = 0; k < a.d; k++) {
        c.data[j * a.d + i] += a.data[k * a.d + i] * b.data[j * a.d + k];
      }
    }
  }
  return c;
}

M M_I(const size_t d) {
  M m;

  m.d = 4;
  m.data = malloc(16 * sizeof(float));

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

  m.d = 4;
  m.data = malloc(16 * sizeof(float));

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

  M m;

  m.d = 4;
  m.data = malloc(16 * sizeof(float));

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

  M m;

  m.d = 4;
  m.data = malloc(16 * sizeof(float));

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

  M m;

  m.d = 4;
  m.data = malloc(16 * sizeof(float));

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
  M m;

  m.d = 4;
  m.data = malloc(16 * sizeof(float));

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

  M m;

  m.d = 4;
  m.data = malloc(16 * sizeof(float));

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
  for (size_t i = 0; i < m.d; i++) {
    printf("  [");
    for (size_t j = 0; j < m.d; j++) {
      printf("%f, ", m.data[j * m.d + i]);
    }
    printf("]\n");
  }
  printf("]\n");
}

void M_free(M m) { free(m.data); }
