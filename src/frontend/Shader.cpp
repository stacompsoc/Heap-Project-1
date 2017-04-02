#include "Shader.hpp"
#include "Log.hpp"

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <sys/stat.h>

Shader::Shader(std::string &filename):
  filename(filename)
{
  if(false) {
  } else if(is_ext(".vert")) {
    type = GL_VERTEX_SHADER;
  } else if(is_ext(".tesc")) {
    type = GL_TESS_CONTROL_SHADER;
  } else if(is_ext(".tese")) {
    type = GL_TESS_EVALUATION_SHADER;
  } else if(is_ext(".geom")) {
    type = GL_GEOMETRY_SHADER;
  } else if(is_ext(".frag")) {
    type = GL_FRAGMENT_SHADER;
  } else if(is_ext(".comp")) {
    type = GL_COMPUTE_SHADER;
  }
  // else type == 0
}

Shader::~Shader()
{}

bool Shader::is_ext(const std::string &&ext) {
  if(ext.length() > filename.length())
    return false;
  size_t f=filename.length(),e=ext.length();
  return filename.substr(f-e, e) == ext;
}

size_t Shader::file_length() {
  struct stat st;
  stat(filename.c_str(), &st);
  return st.st_size;
}

char *Shader::load_text_file() {
  size_t size = file_length() + 1;
  char *text = (char *)malloc(size * sizeof(char));
  assert(text != NULL);

  FILE *file = fopen(filename.c_str(), "r");
  assert(file != NULL);

  char *t = text;
  while((*t = fgetc(file)) != EOF) {
    ++t;
  }
  *t = '\0';

  fclose(file);
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
