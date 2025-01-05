#version 330 core

layout (location = 0) in vec3 position;

uniform float time;
uniform mat4 mat;

out vec3 vPos;

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main() {
    float wave1 = sin(position.x * 2.0 + time * 4) * 0.1;
    float wave2 = sin(position.z * 3.0 + time * 7) * 0.05;

    float rand = random(position.xz) / 3.0f;

    float displacement = wave1 + wave2 + rand;
    vec3 displacedPos = position + vec3(0.0, displacement, 0.0);

    vPos = displacedPos;
    gl_Position = mat * vec4(displacedPos, 1.0);
}


