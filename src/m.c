#include "m.h"

struct m {
  size_t d;
  float *data;
};

M *M_new(const size_t d) {
  M *m = malloc(sizeof(M));
  m->d = d;
  m->data = calloc(d * d, sizeof(float));
  return m;
}

M *M_mul(const M *a, const M *b) {
  M *c = M_new(a->d);
  for (size_t i = 0; i < a->d; i++) {
    for (size_t j = 0; j < a->d; j++) {
      for (size_t k = 0; k < a->d; k++) {
        c->data[i * a->d + j] += a->data[i * a->d + k] * b->data[k * a->d + j];
      }
    }
  }
  return c;
}

M *M_I(const size_t d) {
  M *m = M_new(d);
  for (size_t i = 0; i < d; i++) {
    m->data[i * d + i] = 1;
  }
  return m;
}
