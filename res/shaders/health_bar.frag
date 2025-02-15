#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform float health_percent;

void main() {
    // Use the x texture coordinate to determine color
    if (TexCoord.x > health_percent) {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);  // Red
    } else {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);  // Green
    }
} 