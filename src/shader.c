#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

#include "shader.h"

struct shader {
  GLuint gl_shader_program_id;
};

int create_individual_shader(const char *shader, GLenum type) {
  int shader_id = glCreateShader(type);

  glShaderSource(shader_id, 1, &shader, NULL);
  glCompileShader(shader_id);

  GLint success;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    GLint log_size;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_size);

    char *log = malloc(log_size);
    glGetShaderInfoLog(shader_id, log_size, NULL, log);

    printf("Failed to compile shader: %s\n", log);

    free(log);

    return -1;
  }

  return shader_id;
}

Shader *Shader_new(const char *vertex_shader_source,
                   const char *fragment_shader_source) {
  int program_id = glCreateProgram();

  int vertex_shader_id =
      create_individual_shader(vertex_shader_source, GL_VERTEX_SHADER);

  if (vertex_shader_id == -1) {
    return NULL;
  }

  int fragment_shader_id =
      create_individual_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

  if (fragment_shader_id == -1) {
    return NULL;
  }

  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);

  glLinkProgram(program_id);

  GLint success;
  glGetProgramiv(program_id, GL_LINK_STATUS, &success);

  if (success == GL_FALSE) {
    GLint log_size;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);

    char *log = malloc(log_size);
    glGetProgramInfoLog(program_id, log_size, NULL, log);

    printf("Failed to link program: %s\n", log);

    free(log);

    return NULL;
  }


  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  Shader *shader = malloc(sizeof(Shader));

  shader->gl_shader_program_id = program_id;

  return shader;
}

void Shader_bind(Shader *shader) {
  glUseProgram(shader->gl_shader_program_id);
}
