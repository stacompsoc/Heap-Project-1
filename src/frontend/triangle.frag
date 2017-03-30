#version 400

uniform sampler2D samp;

in vec2 ftexcoords;

out vec4 frag_color;

void main(void) {
  frag_color = texture(samp, ftexcoords).rgba;
}
