#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include "../math/m.h"

typedef struct {
  GLuint gl_shader_program_id;
} Shader;

Shader Shader_new(const char *vertex_shader_source,
                  const char *fragment_shader_source);
void Shader_bind(const Shader shader);
void Shader_set_uniform_m(const Shader *shader, const char *name, const M *m);

Shader get_currently_bound_shader();

#endif // !SHADER_H
