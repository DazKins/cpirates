#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

typedef struct {
  GLuint gl_texture_id;
} Texture;

Texture Texture_load_from_image(const char* path);

void Texture_bind(Texture *texture);

#endif // !TEXTURE_H
