#pragma once

#include "incgraphics.h"

struct VertexArray {
  GLuint id = 0;
  int number_of_buffers = 0;
  VertexArray();
  ~VertexArray();
  void Init();
  GLuint get_id() const;
  void EnableBuffer(GLuint buffer);
  void Bind();
  static void Unbind();
  void Clear();
};
