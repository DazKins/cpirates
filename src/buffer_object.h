#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include <stdlib.h>

#include "vec.h"

struct bufferObject;
typedef struct bufferObject BufferObject;

BufferObject *BufferObject_new(const size_t vertex_count,
                               const V3 *positions,
                               const size_t index_count,
                               const unsigned int *indices);

void BufferObject_render(BufferObject *buffer_object);

#endif // !BUFFER_OBJECT_H
