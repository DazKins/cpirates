#ifndef VEC_H
#define VEC_H

struct v;
typedef struct v V;

V *V_new(const float x, const float y, const float z);

float V_getX(const V *v);
float V_getY(const V *v);
float V_getZ(const V *v);

#endif // !VEC_H
