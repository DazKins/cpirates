#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include <stdlib.h>

#include "../math/v.h"
#include "../util/list.h"
#include "model.h"

typedef struct {
  V _pos;

  List _positions;
  List _indices;

  size_t _positions_count;
  size_t _indices_count;
} ModelBuilder;

ModelBuilder ModelBuilder_new();

void ModelBuilder_push_position(ModelBuilder *mb, V pos);
void ModelBuilder_push_index(ModelBuilder *mb, const unsigned int index);

Model *ModelBuilder_build(ModelBuilder *mb);

#endif // !MODEL_BUILDER_H
