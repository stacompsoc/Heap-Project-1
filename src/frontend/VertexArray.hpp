#pragma once

#include <vector>
#include "incgraphics.h"

namespace gl {
struct VertexArray {
  static GLuint last_vao;
  GLuint id = 0;
  VertexArray();
  ~VertexArray();
  void Init();
  GLuint get_id() const;
  void Bind();
  static void Unbind();
  void Clear();
};
}
