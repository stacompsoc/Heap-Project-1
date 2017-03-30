#version 400

uniform mat4 model;
uniform mat4 camera;

layout (location = 0) in vec3 vposition;
layout (location = 1) in vec2 vtexcoords;

out vec2 gtexcoords;
out float gshade;

void main() {
  gtexcoords = vtexcoords;
  gl_Position = camera * model * vec4(vposition, 1.0);
  gshade = 1 - gl_Position.z;
  if(gshade > 1.5)gshade = 1.5;
}
