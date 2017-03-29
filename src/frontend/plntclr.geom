#version 400

layout (triangles, invocations = 1) in;
layout (triangle_strip, max_vertices = 3) out;

in vec4 gcolor[3];
out vec4 fcolor;

void main() {
  fcolor = gcolor[0];
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  fcolor = gcolor[1];
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();
  fcolor = gcolor[2];
  gl_Position = gl_in[2].gl_Position;
  EmitVertex();
  EndPrimitive();
}
