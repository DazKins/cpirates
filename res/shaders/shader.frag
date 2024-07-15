#version 330 core

out vec4 fragColor;

uniform sampler2D u_texture;

in vec2 v_texCoord;

void main() {
  fragColor = texture(u_texture, v_texCoord);
}

