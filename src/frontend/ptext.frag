#version 400

in vec2 ftexcoords;
out vec4 frag_color;

uniform sampler2D samp;
uniform vec3 textcolor;

void main(void) {
  float res = texture(samp, ftexcoords).r;
  if(res > .5) {
    frag_color = vec4(textcolor, 1.0);
  } else {
    frag_color = vec4(1.0, 1.0, 1.0, 0.0);
  }
}
