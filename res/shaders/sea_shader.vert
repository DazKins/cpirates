#version 330 core

layout (location = 0) in vec3 position;

uniform float time;
uniform mat4 mat;

out vec3 vPos;

// Random function
float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main() {
    // Random offset based on position to make the waves less uniform
    float randOffset = random(position.xz) * 2.0 * 3.14159;

    // Directional randomisation to avoid uniform movement
    float wave1 = sin(position.x * 2.0 + time * 4.0 + randOffset) * 0.08;
    float wave2 = sin(position.z * 3.0 + time * 6.5 - randOffset) * 0.06;
    float wave3 = sin((position.x + position.z) * 1.5 + time * 2.0 + randOffset * 0.5) * 0.04;

    // Time-varying random displacement to add chaotic ripples
    float timeRand = random(vec2(time, position.x + position.z)) * 0.02;

    // Combine waves with random time offset
    float displacement = wave1 + wave2 + wave3 + timeRand;

    // Apply displacement
    vec3 displacedPos = position + vec3(0.0, displacement, 0.0);

    vPos = displacedPos;
    gl_Position = mat * vec4(displacedPos, 1.0);
}
