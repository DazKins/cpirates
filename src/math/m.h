#ifndef MAT_H
#define MAT_H

#include "v.h"
#include <stdlib.h>

typedef struct {
  size_t d;
  float *data;
} M;

M M_new(const size_t d);

M M_mul(const M a, const M b);

M M_I(const size_t d);
M M_Translate(V v);
M M_RotX(float a);
M M_RotY(float a);
M M_RotZ(float a);
M M_Scale(V v);

void M_free(M m);

#endif // !MAT_H
