#pragma once

#include "incgraphics.h"
#include "ShaderAttrib.hpp"

namespace gl {
struct ColorBuffer {
  GLuint vbo = 0;
  ColorBuffer();
  ~ColorBuffer();
  void Init(const GLfloat *buffer);
  void Clear();
};
}
