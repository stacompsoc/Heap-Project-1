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
  gshade = 1;
  /* gshade = .5 - gl_Position.z + sqrt(gl_Position.x*gl_Position.x + gl_Position.y*gl_Position.y); */
  /* if(gshade > 1.0) */
  /*   gshade = 1.0; */
}
