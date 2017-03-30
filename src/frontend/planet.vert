#version 400

uniform mat4 model;
uniform mat4 camera;

layout (location = 0) in vec3 vposition;
layout (location = 1) in vec2 vtexcoords;

out vec2 gtexcoords;

void main() {
  gtexcoords = vtexcoords;
  gl_Position = model * vec4(vposition, 1.0);
}
