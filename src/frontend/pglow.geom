#version 400

layout (triangles, invocations = 1) in;
layout (points, max_vertices = 1) out;

in vec2 gtexcoords[3];
in float gshade[3];
out vec2 ftexcoords;
out float fshade;

void main() {
  ftexcoords = gtexcoords[0];
  fshade = gshade[0];
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  ftexcoords = gtexcoords[1];
  fshade = gshade[1];
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();
  EndPrimitive();
}
