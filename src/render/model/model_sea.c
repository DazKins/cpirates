#include "model_sea.h"

void ModelSea_build(ModelBuilder *model_builder) {
  float size = 100.0f;
  int grid_resolution = 100;

  float step_size = size / grid_resolution;

  float tex_size = 16.0f / 512.0f;

  for (int x = 0; x < grid_resolution; x++) {
    for (int z = 0; z < grid_resolution; z++) {
      V v00 = V_new((x + 0) * step_size - size / 2.0f, 0, (z + 0) * step_size - size / 2.0f);
      V v01 = V_new((x + 0) * step_size - size / 2.0f, 0, (z + 1) * step_size - size / 2.0f);
      V v10 = V_new((x + 1) * step_size - size / 2.0f, 0, (z + 0) * step_size - size / 2.0f);
      V v11 = V_new((x + 1) * step_size - size / 2.0f, 0, (z + 1) * step_size - size / 2.0f);

      V2 uv00 = V2_new(1 * tex_size, 0 * tex_size);
      V2 uv01 = V2_new(1 * tex_size, 1 * tex_size);
      V2 uv10 = V2_new(2 * tex_size, 0 * tex_size);
      V2 uv11 = V2_new(2 * tex_size, 1 * tex_size);

      ModelBuilder_push_quad(model_builder, v00, uv00, v01, uv01, v11, uv11, v10, uv10);
    }
  }

  return;
}