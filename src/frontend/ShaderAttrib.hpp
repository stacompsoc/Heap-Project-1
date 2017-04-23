#pragma once

#include <string>
#include "incgraphics.h"

struct ShaderAttrib {
  std::string location = "";
  GLuint vbo = 0;
  GLenum type;
  ShaderAttrib();
  ShaderAttrib(const char *loc);
  ~ShaderAttrib();
  void Init(GLenum vbotype);
  GLuint get_id();
  GLuint get_loc(GLuint program_id);
  void Bind();
  void Clear();
};
