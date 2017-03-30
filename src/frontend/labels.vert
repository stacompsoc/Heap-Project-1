#version 400

layout (location = 0) in vec3 vposition;
layout (location = 1) in vec2 intexcoord;

out vec2 outtexcoord;

void main() {
  outtexcoord = intexcoord;
  gl_Position = vec4(vposition, 1);
}
