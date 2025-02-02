#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <stdlib.h>

#include "math/v.h"
#include "render/shader.h"

typedef struct {
  GLuint _vao_id;
  size_t _index_count;
  Shader shader;
} Model;

Model Model_new(const size_t vertex_count, const V *positions,
                const V2 *tex_coords, const size_t index_count,
                const unsigned int *indices, Shader shader);

void Model_render(const Model *buffer_object);

#endif // !MODEL_H
