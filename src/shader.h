#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct shader {
  GLuint gl_shader_program_id;
} Shader;

Shader Shader_new(const char *vertex_shader_source,
                  const char *fragment_shader_source);
void Shader_bind(Shader shader);

#endif // !SHADER_H
