#version 400

layout (location = 0) in vec3 vposition;
layout (location = 1) in vec2 vtexcoords;

out vec2 gtexcoords;
out vec4 gcolor;

void main(void) {
  gl_Position = vec4(vposition, 1.0);
  gtexcoords = vtexcoords;
}
