#include "Shader.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

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

void Shader::Compile() {
  id = glCreateShader(type); GLERROR
  char *source_code = file.load_text();
  ASSERT(source_code != NULL);
  glShaderSource(id, 1, &source_code, NULL); GLERROR
  glCompileShader(id); GLERROR
  free(source_code);
}
