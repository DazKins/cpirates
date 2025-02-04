#ifndef MAT_H
#define MAT_H

#include <stdlib.h>

#include "math/v.h"

typedef struct {
  float data[16];
} M;

M M_new();

M M_mul(const M a, const M b);

M M_I();
M M_Translate(V v);
M M_RotX(float a);
M M_RotY(float a);
M M_RotZ(float a);
M M_Scale(V v);
M M_perspective(float fov, float aspect, float near, float far);

void M_print(M m);

#endif // !MAT_H
