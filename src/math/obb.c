#include "obb.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// Helper function to compute absolute value of a float.
static float f_abs(float x) { return (x < 0.0f) ? -x : x; }

OBB OBB_new(V center, V half_extents, V axes[3]) {
  OBB obb;
  obb.center = center;
  obb.half_extents = half_extents;
  for (int i = 0; i < 3; i++) {
    obb.axis[i] = axes[i];
  }
  return obb;
}

OBB OBB_new_sym(V half_extents, V axes[3]) {
  OBB obb;
  obb.center = V_new(0.0f, 0.0f, 0.0f); // Centered at the origin.
  obb.half_extents = half_extents;
  for (int i = 0; i < 3; i++) {
    obb.axis[i] = axes[i];
  }
  return obb;
}

OBB OBB_translate(OBB obb, V v) {
  obb.center = V_add(obb.center, v);
  return obb;
}

OBB OBB_rotate(OBB obb, float angle, V axis) {
  // Rotate the OBB about its center. The center remains unchanged.
  // The half_extents represent the half lengths along the local axes and remain
  // unchanged.
  OBB rotated = obb; // Copy center and half_extents.
  for (int i = 0; i < 3; i++) {
    float dot_val = V_dot(obb.axis[i], axis);
    V cross_val = V_cross(axis, obb.axis[i]);
    // Invert the rotation by negating the sine term.
    V new_axis = V_add(
        V_add(V_mul(obb.axis[i], cosf(angle)), V_mul(cross_val, -sinf(angle))),
        V_mul(axis, dot_val * (1.0f - cosf(angle))));
    rotated.axis[i] = V_norm(new_axis);
  }
  return rotated;
}

const char *OBB_to_string(OBB obb) {
  char *str = malloc(256);
  const char *center_str = V_to_string(obb.center);
  const char *half_str = V_to_string(obb.half_extents);
  const char *axis0_str = V_to_string(obb.axis[0]);
  const char *axis1_str = V_to_string(obb.axis[1]);
  const char *axis2_str = V_to_string(obb.axis[2]);
  sprintf(str, "OBB(center: %s, half_extents: %s, axes: [%s, %s, %s])",
          center_str, half_str, axis0_str, axis1_str, axis2_str);
  return str;
}

int OBB_intersects(OBB obb1, OBB obb2) {
  float R[3][3], absR[3][3];
  // Compute rotation matrix expressing obb2 in obb1's coordinate frame.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R[i][j] = V_dot(obb1.axis[i], obb2.axis[j]);
      absR[i][j] = f_abs(R[i][j]) +
                   1e-6f; // Add small epsilon to counteract arithmetic errors.
    }
  }

  // Compute translation vector t from obb1.center to obb2.center and express it
  // in obb1's coordinate frame.
  V t_vec = V_sub(obb2.center, obb1.center);
  float t[3] = {V_dot(t_vec, obb1.axis[0]), V_dot(t_vec, obb1.axis[1]),
                V_dot(t_vec, obb1.axis[2])};

  // Convenience arrays for the half extents.
  float a[3] = {obb1.half_extents.x, obb1.half_extents.y, obb1.half_extents.z};
  float b[3] = {obb2.half_extents.x, obb2.half_extents.y, obb2.half_extents.z};
  float ra, rb, t_proj;

  // Test axes L = A0, A1, A2 (the obb1's local axes).
  for (int i = 0; i < 3; i++) {
    ra = a[i];
    rb = b[0] * absR[i][0] + b[1] * absR[i][1] + b[2] * absR[i][2];
    if (f_abs(t[i]) > ra + rb)
      return 0;
  }

  // Test axes L = B0, B1, B2 (the obb2's local axes).
  for (int j = 0; j < 3; j++) {
    ra = a[0] * absR[0][j] + a[1] * absR[1][j] + a[2] * absR[2][j];
    rb = b[j];
    t_proj = f_abs(t[0] * R[0][j] + t[1] * R[1][j] + t[2] * R[2][j]);
    if (t_proj > ra + rb)
      return 0;
  }

  // Test axis L = A0 x B0.
  t_proj = f_abs(t[2] * R[1][0] - t[1] * R[2][0]);
  ra = a[1] * absR[2][0] + a[2] * absR[1][0];
  rb = b[1] * absR[0][2] + b[2] * absR[0][1];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A0 x B1.
  t_proj = f_abs(t[2] * R[1][1] - t[1] * R[2][1]);
  ra = a[1] * absR[2][1] + a[2] * absR[1][1];
  rb = b[0] * absR[0][2] + b[2] * absR[0][0];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A0 x B2.
  t_proj = f_abs(t[2] * R[1][2] - t[1] * R[2][2]);
  ra = a[1] * absR[2][2] + a[2] * absR[1][2];
  rb = b[0] * absR[0][1] + b[1] * absR[0][0];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A1 x B0.
  t_proj = f_abs(t[0] * R[2][0] - t[2] * R[0][0]);
  ra = a[0] * absR[2][0] + a[2] * absR[0][0];
  rb = b[1] * absR[1][2] + b[2] * absR[1][1];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A1 x B1.
  t_proj = f_abs(t[0] * R[2][1] - t[2] * R[0][1]);
  ra = a[0] * absR[2][1] + a[2] * absR[0][1];
  rb = b[0] * absR[1][2] + b[2] * absR[1][0];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A1 x B2.
  t_proj = f_abs(t[0] * R[2][2] - t[2] * R[0][2]);
  ra = a[0] * absR[2][2] + a[2] * absR[0][2];
  rb = b[0] * absR[1][1] + b[1] * absR[1][0];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A2 x B0.
  t_proj = f_abs(t[1] * R[0][0] - t[0] * R[1][0]);
  ra = a[0] * absR[1][0] + a[1] * absR[0][0];
  rb = b[1] * absR[2][2] + b[2] * absR[2][1];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A2 x B1.
  t_proj = f_abs(t[1] * R[0][1] - t[0] * R[1][1]);
  ra = a[0] * absR[1][1] + a[1] * absR[0][1];
  rb = b[0] * absR[2][2] + b[2] * absR[2][0];
  if (t_proj > ra + rb)
    return 0;

  // Test axis L = A2 x B2.
  t_proj = f_abs(t[1] * R[0][2] - t[0] * R[1][2]);
  ra = a[0] * absR[1][2] + a[1] * absR[0][2];
  rb = b[0] * absR[2][1] + b[1] * absR[2][0];
  if (t_proj > ra + rb)
    return 0;

  // No separating axis found; the OBBs intersect.
  return 1;
}
