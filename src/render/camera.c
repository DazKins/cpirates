#include "camera.h"

#include <math.h>

#include "util/input.h"
#include "util/keys.h"

Camera Camera_new(float aspect_ratio, float fov, float near, float far) {
  Camera camera;

  camera.pos = V_new(0, 0, 0);
  camera.rot = V_new(0, 0, 0);

  camera.aspect_ratio = aspect_ratio;
  camera.fov = fov;
  camera.near = near;
  camera.far = far;

  return camera;
}

M Camera_get_transform(Camera *camera) {
  M transform = M_perspective(camera->fov, camera->aspect_ratio, camera->near, camera->far);
  transform = M_mul(transform, M_RotX(-camera->rot.x));
  transform = M_mul(transform, M_RotY(-camera->rot.y));
  transform = M_mul(transform, M_RotZ(-camera->rot.z));
  transform = M_mul(transform, M_Translate(V_neg(&camera->pos)));
  return transform;
}

void Camera_process_input(Camera *camera) {
  if (Input_is_key_down(KEY_W)) {
    camera->pos.x += sin(camera->rot.y) * 0.01f;
    camera->pos.z -= cos(camera->rot.y) * 0.01f;
  }

  if (Input_is_key_down(KEY_S)) {
    camera->pos.x -= sin(camera->rot.y) * 0.01f;
    camera->pos.z += cos(camera->rot.y) * 0.01f;
  }

  if (Input_is_key_down(KEY_A)) {
    camera->pos.x -= cos(camera->rot.y) * 0.01f;
    camera->pos.z -= sin(camera->rot.y) * 0.01f;
  }

  if (Input_is_key_down(KEY_D)) {
    camera->pos.x += cos(camera->rot.y) * 0.01f;
    camera->pos.z += sin(camera->rot.y) * 0.01f;
  }

  if (Input_is_key_down(KEY_SPACE)) {
    camera->pos.y += 0.01f;
  }

  if (Input_is_key_down(KEY_LEFT_SHIFT)) {
    camera->pos.y -= 0.01f;
  }

  camera->rot.y += Input_get_mouse_delta().x * 0.003f;
  camera->rot.x += Input_get_mouse_delta().y * 0.003f;
}

void Camera_look_at(Camera *camera, V pos, float dist, float azimuth, float elevation) {
  camera->pos.x = pos.x + sin(azimuth) * cos(elevation) * dist;
  camera->pos.y = pos.y + sin(elevation) * dist;
  camera->pos.z = pos.z + cos(azimuth) * cos(elevation) * dist;

  camera->rot.x = elevation;
  camera->rot.y = -azimuth;
  camera->rot.z = 0;
}

V Camera_get_look_vector(Camera *camera) {
  V look_vector;
  look_vector.x = sin(camera->rot.y) * cos(camera->rot.x);
  look_vector.y = sin(camera->rot.x);
  look_vector.z = -cos(camera->rot.y) * cos(camera->rot.x);
  return look_vector;
}
