#version 400

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 vposition;
layout (location = 1) in vec4 vcolor;

out vec4 color;

void main() {
  color = vcolor;
  gl_Position = vec4(vposition, 1.0) * view;
}
