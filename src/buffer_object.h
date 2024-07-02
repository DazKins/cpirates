#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include <glad/glad.h>
#include <stdlib.h>

#include "v.h"

typedef struct bufferObject {
  GLuint vao_id;
  size_t index_count;
} BufferObject;

BufferObject BufferObject_new(const size_t vertex_count, const V *positions,
                              const size_t index_count,
                              const unsigned int *indices);

void BufferObject_render(BufferObject *buffer_object);

#endif // !BUFFER_OBJECT_H
