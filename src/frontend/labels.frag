#version 400

uniform sampler2D tex;
in vec2 frag_tex_coord;
out vec4 final_tex_coord;

void main() {
  final_tex_coord = texture(tex, frag_tex_coord);
}
