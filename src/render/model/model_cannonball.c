#include "model_cannonball.h"

#include "render/model/model_builder.h"

Model *model_cannonball;

Model *ModelCannonball_build() {
  if (model_cannonball != NULL) {
    return model_cannonball;
  }

  ModelBuilder model_builder = ModelBuilder_new();

  float size = 0.4f;
  float half_size = size / 2.0f;

  float texSize = 16.0f / 512.0f;

  V2 uv00 = V2_new(3 * texSize, 0 * texSize);
  V2 uv01 = V2_new(3 * texSize, 1 * texSize);
  V2 uv10 = V2_new(4 * texSize, 0 * texSize);
  V2 uv11 = V2_new(4 * texSize, 1 * texSize);

  V v0 = V_new(-half_size, -half_size, -half_size);
  V v1 = V_new(half_size, -half_size, -half_size);
  V v2 = V_new(-half_size, half_size, -half_size);
  V v3 = V_new(half_size, half_size, -half_size);
  V v4 = V_new(-half_size, -half_size, half_size);
  V v5 = V_new(half_size, -half_size, half_size);
  V v6 = V_new(-half_size, half_size, half_size);
  V v7 = V_new(half_size, half_size, half_size);

  ModelBuilder_push_single_texture_cube(&model_builder, uv00, uv01, uv10, uv11,
                                        v0, v1, v2, v3, v4, v5, v6, v7);

  model_cannonball = ModelBuilder_build(&model_builder);

  return model_cannonball;
}
