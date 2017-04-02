#version 400

uniform mat4 model;
uniform mat4 projection;

layout (location = 0) in vec3 vposition;
layout (location = 1) in vec2 vtexcoords;

out vec2 ftexcoords;

void main() {
  ftexcoords = vtexcoords;
  gl_Position = projection * model * vec4(vposition, 1.0);
}
