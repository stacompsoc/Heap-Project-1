#pragma once

#include <glm/glm.hpp>
#include "Shape.hpp"
#include "Triangle.hpp"
#include "VertexArray.hpp"
#include "ShaderAttrib.hpp"

template <int N>
class Ring : public Shape {
protected:
  gl::VertexArray vao;
  gl::ShaderAttrib
    vert, tex;
  GLfloat
    *vertices = NULL,
    *txcoords = NULL;
  static const size_t DIM;
  static const size_t SIZE;
  void SetTexcoords(int index);
  void SetVertices(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, size_t index);
public:
  Ring();
  ~Ring();
  void Init();
  void InitBuffers();
  void Draw();
  void Clear();
};
