#ifndef VEC_H
#define VEC_H

typedef struct {
  float x;
  float y;
  float z;
} V;

typedef struct {
  float x;
  float y;
} V2;

V V_new(const float x, const float y, const float z);
V2 V2_new(const float x, const float y);

V V_neg(const V *v);

V2 V2_sub(const V2 *a, const V2 *b);

#endif // !VEC_H
