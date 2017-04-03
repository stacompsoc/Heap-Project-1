#version 400

uniform sampler2D samp;

in float fshade;
in vec2 ftexcoords;

out vec4 frag_color;

void main() {
  frag_color = fshade * texture(samp, ftexcoords).rgba;
}
