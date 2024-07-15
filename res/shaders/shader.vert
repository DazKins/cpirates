#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 mat;

out vec2 v_texCoord;

void main() {
  v_texCoord = texCoord;
  gl_Position = mat * vec4(position, 1.0);
}

