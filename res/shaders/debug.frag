#version 330 core

uniform vec3 debugColor; // Debug colour

out vec4 FragColor;

void main() {
    FragColor = vec4(debugColor, 1.0); // Set the output colour
}
