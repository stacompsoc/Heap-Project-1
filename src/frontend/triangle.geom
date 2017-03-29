#version 400

layout (triangles, invocations = 1) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 gtexcoords[3];

out vec2 ftexcoords;

void main() {
  ftexcoords = gtexcoords[0];
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  ftexcoords = gtexcoords[1];
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();
  ftexcoords = gtexcoords[2];
  gl_Position = gl_in[2].gl_Position;
  EmitVertex();
  EndPrimitive();
}
