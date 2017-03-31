#version 400

in vec2 ftexcoords;
out vec4 fcolor;

uniform sampler2D text;
uniform vec3 textcolor;

void main(void) {
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, ftexcoords).r);
  fcolor = vec4(textcolor, 1.0) * sampled;
}
