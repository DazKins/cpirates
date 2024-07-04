#ifndef VEC_H
#define VEC_H

typedef struct {
  float x;
  float y;
  float z;
} V;

V V_new(const float x, const float y, const float z);

#endif // !VEC_H
