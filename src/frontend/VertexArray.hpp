#pragma once

#include <vector>
#include "incgraphics.h"

#include "ShaderAttrib.hpp"

namespace gl {
struct VertexArray {
  static GLuint last_vao;
  GLuint id = 0;
  std::vector<gl::Attrib> attribs;

  VertexArray();
  ~VertexArray();
  void Init();
  GLuint get_id() const;
  void Bind();
  void Enable(gl::Attrib &attrib);
  static void Unbind();
  void Clear();
};
}
