#version 330 core

out vec4 fragColor;

uniform sampler2D u_texture;
uniform int team;  // 0 for red team, 1 for blue team

in vec2 v_texCoord;

void main() {
  vec4 texColor = texture(u_texture, v_texCoord);
  
  // Add team coloring with more distinct colors
  vec3 teamColor = team == 0 ? vec3(1.0, 0.0, 0.0) : vec3(0.0, 0.0, 1.0);
  
  // Mix the texture color with the team color more strongly
  fragColor = vec4(mix(texColor.rgb, teamColor, 0.5), texColor.a);
} 