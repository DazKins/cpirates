#include "model_builder.h"
#include "model.h"

ModelBuilder ModelBuilder_new() {
  ModelBuilder mb;
  return mb;
}

void ModelBuilder_set_position(ModelBuilder *mb, V pos) { mb->_pos = pos; }

void ModelBuilder_set_tex_coord(ModelBuilder *mb, V2 tex_coord) {
  mb->_tex_coord = tex_coord;
}

void ModelBuilder_push_vertex(ModelBuilder *mb) {
  V *pos = malloc(sizeof(V));
  V2 *tex_coord = malloc(sizeof(V2));

  *pos = mb->_pos;
  *tex_coord = mb->_tex_coord;

  List_push(&mb->_positions, pos);
  List_push(&mb->_tex_coords, tex_coord);

  mb->_vertices_count++;
}

void ModelBuilder_push_index(ModelBuilder *mb, unsigned int index) {
  unsigned int *index_copy = malloc(sizeof(unsigned int));
  *index_copy = index;
  List_push(&mb->_indices, index_copy);
  mb->_indices_count++;
}

Model *ModelBuilder_build(ModelBuilder *mb) {
  V *positions = malloc(sizeof(V) * mb->_vertices_count);

  Iterator positions_iter = Iterator_new(&mb->_positions);
  int i = 0;
  while (Iterator_has_next(&positions_iter)) {
    V *pos = Iterator_next(&positions_iter);
    positions[i++] = *pos;
  }

  V2 *tex_coords = malloc(sizeof(V2) * mb->_vertices_count);

  Iterator tex_coords_iter = Iterator_new(&mb->_tex_coords);
  i = 0;
  while (Iterator_has_next(&tex_coords_iter)) {
    V2 *tex_coord = Iterator_next(&tex_coords_iter);
    tex_coords[i++] = *tex_coord;
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
  List_free(mb->_tex_coords);
  mb->_tex_coords = List_new();
  List_free(mb->_indices);
  mb->_indices = List_new();

  Model *model = malloc(sizeof(Model));
  *model = Model_new(mb->_vertices_count, positions, tex_coords,
                     mb->_indices_count, raw_indices);

  return model;
}
