#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include <stdlib.h>

#include "math/v.h"
#include "model.h"
#include "render/shader.h"
#include "util/list.h"

typedef struct {
  V _pos;
  V2 _tex_coord;

  List _positions;
  List _tex_coords;
  List _indices;

  size_t _vertices_count;
  size_t _indices_count;

  Shader shader;
} ModelBuilder;

ModelBuilder ModelBuilder_new();

void ModelBuilder_set_position(ModelBuilder *mb, V pos);
void ModelBuilder_set_tex_coord(ModelBuilder *mb, V2 tex_coord);
void ModelBuilder_set_shader(ModelBuilder *mb, Shader shader);

unsigned int ModelBuilder_push_vertex(ModelBuilder *mb);

void ModelBuilder_push_index(ModelBuilder *mb, const unsigned int index);

void ModelBuilder_push_quad(ModelBuilder *mb, V v0, V2 uv0, V v1, V2 uv1, V v2,
                            V2 uv2, V v3, V2 uv3);

void ModelBuilder_push_single_texture_cube(ModelBuilder *mb, V2 uv00, V2 uv01,
                                           V2 uv10, V2 uv11, V v0, V v1, V v2,
                                           V v3, V v4, V v5, V v6, V v7);

Model *ModelBuilder_build(ModelBuilder *mb);

#endif // !MODEL_BUILDER_H
