#ifndef CAMERA_H
#define CAMERA_H

#include "math/v.h"
#include "math/m.h"

typedef struct {
  V pos;
  V rot;

  float aspect_ratio;
  float fov;
  float near;
  float far;
} Camera;

Camera Camera_new(float aspect_ratio, float fov, float near, float far);

M Camera_get_transform(Camera *camera);
V Camera_get_look_vector(Camera *camera);
void Camera_process_input(Camera *camera);
void Camera_look_at(Camera *camera, V pos, float dist, float azimuth, float elevation);

#endif // !CAMERA_H
