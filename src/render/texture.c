#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#include "texture.h"

Texture Texture_load_from_image(const char *path) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    fprintf(stderr, "Failed to open file %s\n", path);
  }

  png_structp png =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fprintf(stderr, "Failed to create png struct\n");
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    fprintf(stderr, "Failed to create png info struct\n");
  }

  if (setjmp(png_jmpbuf(png))) {
    fprintf(stderr, "Failed to setjmp\n");
  }

  png_init_io(png, file);
  png_read_info(png, info);

  int width = png_get_image_width(png, info);
  int height = png_get_image_height(png, info);
  png_byte color_type = png_get_color_type(png, info);
  png_byte bit_depth = png_get_bit_depth(png, info);

  if (bit_depth == 16) {
    png_set_strip_16(png);
  }

  if (color_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_palette_to_rgb(png);
  }

  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
    png_set_expand_gray_1_2_4_to_8(png);
  }

  if (png_get_valid(png, info, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(png);
  }

  if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
  }

  if (color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
    png_set_gray_to_rgb(png);
  }

  png_read_update_info(png, info);

  unsigned char *image_data =
      (unsigned char *)malloc(png_get_rowbytes(png, info) * (height));
  if (!image_data) {
    fprintf(stderr, "Failed to allocate memory for image data\n");
    png_destroy_read_struct(&png, &info, NULL);
    fclose(file);
  }

  png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * (height));
  for (int y = 0; y < height; y++) {
    row_pointers[y] = image_data + y * png_get_rowbytes(png, info);
  }

  png_read_image(png, row_pointers);

  fclose(file);
  png_destroy_read_struct(&png, &info, NULL);
  free(row_pointers);

  GLuint gl_texture_id;
  glGenTextures(1, &gl_texture_id);
  glBindTexture(GL_TEXTURE_2D, gl_texture_id);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);
  free(image_data);

  Texture texture;
  texture.gl_texture_id = gl_texture_id;
  return texture;
}

void Texture_bind(Texture *texture) {
  glBindTexture(GL_TEXTURE_2D, texture->gl_texture_id);
}
