#version 330 core

in vec3 vPos;
out vec4 FragColor;

void main() {
    float depth = vPos.y * 0.5 + 0.5;  // Normalise y displacement for colour blending
    vec3 waterColor = mix(vec3(0.1, 0.3, 0.5), vec3(0.3, 0.8, 0.95), depth);

    FragColor = vec4(waterColor, 1.0);
}
