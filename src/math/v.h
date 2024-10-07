#ifndef VEC_H
#define VEC_H

typedef struct {
  float x;
  float y;
  float z;
} V;

extern const V V_0;

typedef struct {
  float x;
  float y;
} V2;

extern const V2 V2_0;
extern const V2 V2_00;
extern const V2 V2_01;
extern const V2 V2_10;
extern const V2 V2_11;

V V_new(const float x, const float y, const float z);
V2 V2_new(const float x, const float y);

V V_neg(const V *v);

V2 V2_sub(const V2 *a, const V2 *b);

#endif // !VEC_H
