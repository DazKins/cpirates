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
void Camera_process_input(Camera *camera);

#endif // !CAMERA_H
