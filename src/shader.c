#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <stdlib.h>

#include "shader.h"

struct shader {
  GLuint gl_shader_program_id;
};

int create_individual_shader(const char *shader, GLenum type) {
  int shader_id = glCreateShader(type);

  glShaderSource(shader_id, 1, &shader, NULL);
  glCompileShader(shader_id);

  return shader_id;
}

Shader *Shader_new(const char *vertex_shader, const char *fragment_shader) {
  int program_id = glCreateProgram();

  int vertex_shader_id =
      create_individual_shader(vertex_shader, GL_VERTEX_SHADER);
  int fragment_shader_id =
      create_individual_shader(fragment_shader, GL_FRAGMENT_SHADER);

  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);

  glLinkProgram(program_id);

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  Shader *shader = malloc(sizeof(Shader));

  shader->gl_shader_program_id = program_id;

  return shader;
}

void Shader_bind(Shader *shader) {
  return glUseProgram(shader->gl_shader_program_id);
}

