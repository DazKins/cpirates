#ifndef SHADER_H
#define SHADER_H

#include <GLFW/glfw3.h>

struct shader;
typedef struct shader Shader;

Shader *Shader_new(const char *vertex_shader_source, const char *fragment_shader_source);
void Shader_bind(Shader *shader);

#endif // !SHADER_H
