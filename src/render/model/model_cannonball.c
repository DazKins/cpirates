#include "model_cannonball.h"

#include "render/model/model_builder.h"

Model *model_cannonball;

Model *ModelCannonball_build() {
  if (model_cannonball != NULL) {
    return model_cannonball;
  }

  ModelBuilder model_builder = ModelBuilder_new();

  // TODO: build cannonball model...

  ModelBuilder_push_quad(
      &model_builder, V_new(0.5f, 0.5f, 0.5f), V2_00, V_new(0.5f, -0.5f, 0.5f),
      V2_01, V_new(-0.5f, -0.5f, 0.5f), V2_11, V_new(-0.5f, 0.5f, 0.5f), V2_10);

  model_cannonball = ModelBuilder_build(&model_builder);

  return model_cannonball;
}
