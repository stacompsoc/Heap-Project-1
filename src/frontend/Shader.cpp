#include "Shader.hpp"
#include "Log.hpp"

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <sys/stat.h>

Shader::Shader(std::string &filename):
  file(filename.c_str())
{
  if(false) {
  } else if(file.is_ext(".vert")) {
    type = GL_VERTEX_SHADER;
  } else if(file.is_ext(".tesc")) {
    type = GL_TESS_CONTROL_SHADER;
  } else if(file.is_ext(".tese")) {
    type = GL_TESS_EVALUATION_SHADER;
  } else if(file.is_ext(".geom")) {
    type = GL_GEOMETRY_SHADER;
  } else if(file.is_ext(".frag")) {
    type = GL_FRAGMENT_SHADER;
  } else if(file.is_ext(".comp")) {
    type = GL_COMPUTE_SHADER;
  }
  // else type == 0
}

Shader::~Shader()
{}

char *Shader::load_text_file() {
  size_t size = file.length() + 1;
  char *text = (char *)malloc(size * sizeof(char));
  assert(text != NULL);

  FILE *fp = fopen(file.name().c_str(), "r");
  assert(fp != NULL);

  char *t = text;
  while((*t = fgetc(fp)) != EOF) {
    ++t;
  }
  *t = '\0';

  fclose(fp);
  return text;
}

void Shader::Compile() {
  id = glCreateShader(type); GLERROR
  char *source_code = load_text_file();
  ASSERT(source_code != NULL);
  glShaderSource(id, 1, &source_code, NULL); GLERROR
  glCompileShader(id); GLERROR
  free(source_code);
}
