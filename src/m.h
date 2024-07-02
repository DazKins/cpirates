#ifndef MAT_H
#define MAT_H

#include <stdlib.h>

typedef struct m {
  size_t d;
  float *data;
} M;

M M_new(const size_t d);
M M_mul(const M a, const M b);
M M_I(const size_t d);
void M_free(M m);

#endif // !MAT_H
