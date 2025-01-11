#include "model_builder.h"

#include "render/model/model.h"

ModelBuilder ModelBuilder_new() {
  ModelBuilder mb;
  mb._indices = List_new();
  mb._positions = List_new();
  mb._tex_coords = List_new();

  mb._indices_count = 0;
  mb._vertices_count = 0;

  mb._pos = V_new(0.0f, 0.0f, 0.0f);
  mb._tex_coord = V2_new(0.0f, 0.0f);
  return mb;
}

void ModelBuilder_set_position(ModelBuilder *mb, V pos) { mb->_pos = pos; }

void ModelBuilder_set_tex_coord(ModelBuilder *mb, V2 tex_coord) {
  mb->_tex_coord = tex_coord;
}

unsigned int ModelBuilder_push_vertex(ModelBuilder *mb) {
  V *pos = malloc(sizeof(V));
  V2 *tex_coord = malloc(sizeof(V2));

  *pos = mb->_pos;
  *tex_coord = mb->_tex_coord;

  List_push(&mb->_positions, pos);
  List_push(&mb->_tex_coords, tex_coord);

  return mb->_vertices_count++;
}

void ModelBuilder_push_index(ModelBuilder *mb, unsigned int index) {
  unsigned int *index_copy = malloc(sizeof(unsigned int));
  *index_copy = index;
  List_push(&mb->_indices, index_copy);
  mb->_indices_count++;
}

void ModelBuilder_push_quad(ModelBuilder *mb, V v0, V2 uv0, V v1, V2 uv1, V v2,
                            V2 uv2, V v3, V2 uv3) {
  ModelBuilder_set_position(mb, v0);
  ModelBuilder_set_tex_coord(mb, uv0);
  unsigned int i0 = ModelBuilder_push_vertex(mb);

  ModelBuilder_set_position(mb, v1);
  ModelBuilder_set_tex_coord(mb, uv1);
  unsigned int i1 = ModelBuilder_push_vertex(mb);

  ModelBuilder_set_position(mb, v2);
  ModelBuilder_set_tex_coord(mb, uv2);
  unsigned int i2 = ModelBuilder_push_vertex(mb);

  ModelBuilder_set_position(mb, v3);
  ModelBuilder_set_tex_coord(mb, uv3);
  unsigned int i3 = ModelBuilder_push_vertex(mb);

  ModelBuilder_push_index(mb, i0);
  ModelBuilder_push_index(mb, i1);
  ModelBuilder_push_index(mb, i2);
  ModelBuilder_push_index(mb, i2);
  ModelBuilder_push_index(mb, i3);
  ModelBuilder_push_index(mb, i0);
}

void ModelBuilder_push_single_texture_cube(ModelBuilder *mb, V2 uv00, V2 uv01,
                                           V2 uv10, V2 uv11, V v000, V v001,
                                           V v010, V v011, V v100, V v101,
                                           V v110, V v111) {
  ModelBuilder_push_quad(mb, v000, uv00, v001, uv01, v011, uv11, v010, uv10);
  ModelBuilder_push_quad(mb, v100, uv00, v101, uv01, v111, uv11, v110, uv10);
  ModelBuilder_push_quad(mb, v000, uv00, v100, uv01, v110, uv11, v010, uv10);
  ModelBuilder_push_quad(mb, v001, uv00, v101, uv01, v111, uv11, v011, uv10);
  ModelBuilder_push_quad(mb, v000, uv00, v001, uv01, v101, uv11, v100, uv10);
  ModelBuilder_push_quad(mb, v010, uv00, v011, uv01, v111, uv11, v110, uv10);
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
