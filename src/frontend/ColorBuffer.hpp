#pragma once

#include "incgraphics.h"
#include "ShaderAttrib.hpp"

struct ColorBuffer {
  GLuint vbo = 0;
  ColorBuffer();
  ~ColorBuffer();
  void Init(const GLfloat *buffer);
  void Clear();
};
