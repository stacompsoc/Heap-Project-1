#version 400

// object-wide transformation
uniform mat4 scale;
uniform mat4 rotate;
uniform mat4 translate;

// world-wide transformation
uniform mat4 view;
uniform mat4 projection;

// attributes
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec2 vtexcoords;

// skip to geometry shader
out vec2 gtexcoords;

void main() {
  gl_Position = translate * rotate * scale * vec4(vposition, 1.0) * view;
  gtexcoords = vtexcoords;
}
