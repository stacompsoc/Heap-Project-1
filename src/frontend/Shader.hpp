#pragma once

#include <string>
#include "incgraphics.h"

#include "File.hpp"

namespace gl {
struct Shader {
  File file;
  GLenum type = 0;
  GLuint id = 0;

  Shader(std::string &filename);
  ~Shader();
  char *load_text_file();
  void Compile();
};
}
