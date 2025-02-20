#include "shader.h"

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/file.h"

Shader *Shader_default;

int Shader_init() {
  const char *vertex_shader_source = load_file("res/shaders/shader.vert");

  if (vertex_shader_source == NULL) {
    printf("Failed to load vertex shader source\n");
    return 1;
  }

  const char *fragment_shader_source = load_file("res/shaders/shader.frag");

  if (fragment_shader_source == NULL) {
    printf("failed to load fragment shader source\n");
    return 1;
  }

  Shader_default = malloc(sizeof(Shader));
  *Shader_default = Shader_new(vertex_shader_source, fragment_shader_source);

  free(vertex_shader_source);
  free(fragment_shader_source);

  if (Shader_default == NULL) {
    printf("failed to create default shader\n");
    return 1;
  }

  return 0;
}

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

Shader Shader_new(const char *vertex_shader_source,
                  const char *fragment_shader_source) {
  Shader shader;
  shader.gl_shader_program_id = -1;

  int program_id = glCreateProgram();

  int vertex_shader_id =
      create_individual_shader(vertex_shader_source, GL_VERTEX_SHADER);

  if (vertex_shader_id == -1) {
    return shader;
  }

  int fragment_shader_id =
      create_individual_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

  if (fragment_shader_id == -1) {
    return shader;
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

    return shader;
    ;
  }

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  shader.gl_shader_program_id = program_id;

  return shader;
}

GLuint cur_bound_gl_shader_program_id = -1;

void Shader_bind(const Shader shader) {
  if (cur_bound_gl_shader_program_id == shader.gl_shader_program_id) {
    return;
  }

  glUseProgram(shader.gl_shader_program_id);
  cur_bound_gl_shader_program_id = shader.gl_shader_program_id;
}

void Shader_unbind() {
  glUseProgram(0);
  cur_bound_gl_shader_program_id = 0;
}

Shader get_currently_bound_shader() {
  Shader shader;
  shader.gl_shader_program_id = cur_bound_gl_shader_program_id;
  return shader;
}

void Shader_set_uniform_m(const Shader *shader, const char *name, const M *m) {
  GLint location = glGetUniformLocation(shader->gl_shader_program_id, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, m->data);
}

void Shader_set_uniform_v(const Shader *shader, const char *name, V v) {
  GLint location = glGetUniformLocation(shader->gl_shader_program_id, name);
  glUniform3f(location, v.x, v.y, v.z);
}

void Shader_set_uniform_f(const Shader *shader, const char *name, float f) {
  GLint location = glGetUniformLocation(shader->gl_shader_program_id, name);
  glUniform1f(location, f);
}

void Shader_set_uniform_i(const Shader *shader, const char *name, int i) {
  GLint location = glGetUniformLocation(shader->gl_shader_program_id, name);
  glUniform1i(location, i);
}
