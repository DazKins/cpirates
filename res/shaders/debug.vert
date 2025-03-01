#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 mat;

void main() {
    gl_PointSize = 2.0;
    gl_Position = mat * vec4(position, 1.0);
}
