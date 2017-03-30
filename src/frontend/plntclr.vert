#version 400

uniform mat4 model;
uniform mat4 camera;

// attributes
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec4 vcolor;

// skip to geometry shader
out vec4 gcolor;

void main() {
  gcolor = vcolor;
  gl_Position = model * vec4(vposition, 1.0);
}
