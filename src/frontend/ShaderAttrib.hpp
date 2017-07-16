#pragma once

#include <string>
#include "incgraphics.h"

namespace gl {
struct Attrib {
  std::string location = "";
  GLuint vbo = 0;
  GLenum type;

  Attrib();
  Attrib(const char *loc);
  ~Attrib();
  void Init(GLenum vbotype);
  GLuint get_id();
  GLuint get_loc(GLuint program_id);
  void Bind();
  template <GLint TYPE>
  static void Unbind();
  void Clear();
};
}
