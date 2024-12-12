#ifndef MAT_H
#define MAT_H

#include <stdlib.h>

#include "math/v.h"

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
M M_perspective(float fov, float aspect, float near, float far);

void M_print(M m);

void M_free(M m);

#endif // !MAT_H
