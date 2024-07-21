#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include <stdlib.h>

#include "../../math/v.h"
#include "../../util/list.h"
#include "model.h"

typedef struct {
  V _pos;
  V2 _tex_coord;

  List _positions;
  List _tex_coords;
  List _indices;

  size_t _vertices_count;
  size_t _indices_count;
} ModelBuilder;

ModelBuilder ModelBuilder_new();

void ModelBuilder_set_position(ModelBuilder *mb, V pos);
void ModelBuilder_set_tex_coord(ModelBuilder *mb, V2 tex_coord);

void ModelBuilder_push_vertex(ModelBuilder *mb);

void ModelBuilder_push_index(ModelBuilder *mb, const unsigned int index);

Model *ModelBuilder_build(ModelBuilder *mb);

#endif // !MODEL_BUILDER_H
