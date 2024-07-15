#include <glad/glad.h>

#include "model.h"

const GLuint POSITION_ATTR_LOCATION = 0;
const GLuint TEXCOORD_ATTR_LOCATION = 1;

Model Model_new(const size_t vertex_count, const V *positions,
                const V2 *tex_coords, const size_t index_count,
                const unsigned int *indices) {

  float *raw_positions = malloc(sizeof(float) * vertex_count * 3);

  for (size_t i = 0; i < vertex_count; i++) {
    V pos = positions[i];

    raw_positions[i * 3 + 0] = pos.x;
    raw_positions[i * 3 + 1] = pos.y;
    raw_positions[i * 3 + 2] = pos.z;
  }

  float *raw_texcoords = malloc(sizeof(float) * vertex_count * 2);

  for (size_t i = 0; i < vertex_count; i++) {
    V2 tex_coord = tex_coords[i];
    raw_texcoords[i * 2 + 0] = tex_coord.x;
    raw_texcoords[i * 2 + 1] = tex_coord.y;
  }

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint positions_buffer;
  glGenBuffers(1, &positions_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, positions_buffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * vertex_count * sizeof(float), raw_positions,
               GL_STATIC_DRAW);

  glVertexAttribPointer(POSITION_ATTR_LOCATION, 3, GL_FLOAT, GL_FALSE,
                        3 * sizeof(float), 0);
  glEnableVertexAttribArray(POSITION_ATTR_LOCATION);

  GLuint texcoords_buffer;
  glGenBuffers(1, &texcoords_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, texcoords_buffer);
  glBufferData(GL_ARRAY_BUFFER, 2 * vertex_count * sizeof(float), raw_texcoords,
               GL_STATIC_DRAW);

  glVertexAttribPointer(TEXCOORD_ATTR_LOCATION, 2, GL_FLOAT, GL_FALSE,
                        2 * sizeof(float), 0);
  glEnableVertexAttribArray(TEXCOORD_ATTR_LOCATION);

  GLuint indices_buffer;
  glGenBuffers(1, &indices_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int),
               indices, GL_STATIC_DRAW);

  free(raw_positions);
  free(raw_texcoords);

  Model model;

  model._vao_id = vao;
  model._index_count = index_count;

  return model;
}

void Model_render(const Model *buffer_object) {
  glBindVertexArray(buffer_object->_vao_id);
  glDrawElements(GL_TRIANGLES, buffer_object->_index_count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
