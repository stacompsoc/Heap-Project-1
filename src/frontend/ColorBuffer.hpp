#pragma once

#include "incgraphics.h"

struct ColorBuffer {
  GLuint vbo = 0;
  ColorBuffer();
  ~ColorBuffer();
  void Init(const GLfloat *buffer);
  void Clear();
};
