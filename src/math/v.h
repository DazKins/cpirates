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

V V_new(float x, float y, float z);
V2 V2_new(float x, float y);

V V_add(V v0, V v1);
V V_sub(V v0, V v1);
V V_mul(V v, float a);
V V_set_x(V v, float x);
V V_set_y(V v, float y);
V V_set_z(V v, float z);
V V_neg(V v);
V V_norm(V v);
V V_cross(V v0, V v1);
int V_eq(V v0, V v1);
V V_clamp(V v, float min, float max);
V V_wrap(V v, float min, float max);

V2 V2_sub(V2 a, V2 b);

char *V_to_string(V v);

#endif // !VEC_H
