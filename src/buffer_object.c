#include <glad/glad.h>

#include "buffer_object.h"

const GLuint POSITION_ATTR_LOCATION = 0;

BufferObject BufferObject_new(const size_t vertex_count, const V *positions,
                               const size_t index_count,
                               const unsigned int *indices) {

  float *raw_positions = malloc(sizeof(float) * vertex_count * 3);

  for (size_t i = 0; i < vertex_count; i++) {
    V pos = positions[i];

    raw_positions[i * 3 + 0] = pos.x;
    raw_positions[i * 3 + 1] = pos.y;
    raw_positions[i * 3 + 2] = pos.z;
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

  GLuint indices_buffer;
  glGenBuffers(1, &indices_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int),
               indices, GL_STATIC_DRAW);

  free(raw_positions);

  BufferObject buffer_object;

  buffer_object.vao_id = vao;
  buffer_object.index_count = index_count;

  return buffer_object;
}

void BufferObject_render(BufferObject *buffer_object) {
  glBindVertexArray(buffer_object->vao_id);
  glDrawElements(GL_TRIANGLES, buffer_object->index_count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
