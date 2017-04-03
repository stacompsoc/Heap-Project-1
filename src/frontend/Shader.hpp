#pragma once

#include <string>
#include "incgraphics.h"

struct Shader {
  std::string filename;
  GLenum type = 0;
  GLuint id = 0;

  Shader(std::string &filename);
  ~Shader();
  bool is_ext(const std::string &&ext);
  size_t file_length();
  char *load_text_file();
  void Compile();
};
