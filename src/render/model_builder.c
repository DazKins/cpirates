#include "model_builder.h"
#include "model.h"

ModelBuilder ModelBuilder_new() {
  ModelBuilder mb;
  return mb;
}

void ModelBuilder_push_position(ModelBuilder *mb, V pos) {
  V *pos_copy = malloc(sizeof(V));
  *pos_copy = pos;
  List_push(&mb->_positions, pos_copy);
  mb->_positions_count++;
}

void ModelBuilder_push_index(ModelBuilder *mb, unsigned int index) {
  unsigned int *index_copy = malloc(sizeof(unsigned int));
  *index_copy = index;
  List_push(&mb->_indices, index_copy);
  mb->_indices_count++;
}

Model *ModelBuilder_build(ModelBuilder *mb) {
  V *positions = malloc(sizeof(V) * mb->_positions_count);

  Iterator positions_iter = Iterator_new(&mb->_positions);
  int i = 0;
  while (Iterator_has_next(&positions_iter)) {
    V *pos = Iterator_next(&positions_iter);
    positions[i++] = *pos;
  }

  unsigned int *raw_indices = malloc(sizeof(unsigned int) * mb->_indices_count);
  Iterator indices_iter = Iterator_new(&mb->_indices);
  i = 0;
  while (Iterator_has_next(&indices_iter)) {
    unsigned int *index = Iterator_next(&indices_iter);
    raw_indices[i++] = *index;
  }

  List_free(mb->_positions);
  mb->_positions = List_new();
  List_free(mb->_indices);
  mb->_indices = List_new();

  Model *model = malloc(sizeof(Model));
  *model = Model_new(mb->_positions_count, positions,
                          mb->_indices_count, raw_indices);

  return model;
}
