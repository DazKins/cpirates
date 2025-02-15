#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 mat;
uniform vec3 position;
uniform vec3 camera_pos;
uniform float width;

out vec2 TexCoord;  // Pass texture coordinates to fragment shader

void main() {
    // Get view direction and create a proper billboard orientation
    vec3 to_camera = normalize(camera_pos - position);
    vec3 right = normalize(cross(vec3(0.0, 1.0, 0.0), to_camera));
    vec3 up = normalize(cross(to_camera, right));  // Calculate actual up vector based on view direction

    // Create billboard-oriented vertex position
    vec3 vertex_pos = position + vec3(0.0, 1.5, 0.0); // Base position above entity
    vertex_pos += right * (aPos.x * width);           // Horizontal offset
    vertex_pos += up * aPos.y * 0.1;                 // Vertical offset

    gl_Position = mat * vec4(vertex_pos, 1.0);
    
    // Pass texture coordinates
    TexCoord = vec2(aPos.x + 0.5, aPos.y);  // Convert from [-0.5, 0.5] to [0, 1] for x coordinate
} 