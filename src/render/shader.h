#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include "math/m.h"

typedef struct {
  GLuint gl_shader_program_id;
} Shader;

extern Shader *Shader_default;

int Shader_init();

Shader Shader_new(const char *vertex_shader_source,
                  const char *fragment_shader_source);
void Shader_bind(const Shader shader);
void Shader_unbind();
void Shader_set_uniform_m(const Shader *shader, const char *name, const M *m);
void Shader_set_uniform_v(const Shader *shader, const char *name, V v);
void Shader_set_uniform_f(const Shader *shader, const char *name, float f);
void Shader_set_uniform_i(const Shader *shader, const char *name, int i);
Shader get_currently_bound_shader();

#endif // !SHADER_H
