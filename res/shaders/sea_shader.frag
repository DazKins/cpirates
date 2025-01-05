#version 330 core

in vec3 vPos;
out vec4 FragColor;

void main() {
    // Normalise y displacement for depth-based colouring
    float depth = clamp(vPos.y * 0.5 + 0.5, 0.0, 1.0);

    // Base water colour
    vec3 deepWaterColor = vec3(0.1, 0.3, 0.5);
    vec3 shallowWaterColor = vec3(0.3, 0.8, 0.95);

    // Add subtle shimmer effect by modulating the depth with a sine wave
    float shimmer = sin(vPos.y * 20.0 + depth * 10.0) * 0.02;

    // Blend the colours based on depth and add the shimmer effect
    vec3 waterColor = mix(deepWaterColor, shallowWaterColor, depth + shimmer);

    FragColor = vec4(waterColor, 1.0);
}
