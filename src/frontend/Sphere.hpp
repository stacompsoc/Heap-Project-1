#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "Shape.hpp"
#include "VertexArray.hpp"
#include "ShaderAttrib.hpp"

class Sphere : public Shape {
  VertexArray vao;
  ShaderAttrib
    vert, tex;
  GLfloat
    *vertices = NULL,
    *txcoords = NULL;
protected:
  static const size_t DIM;
  static const size_t SIZE;
  void SetTexcoords(size_t index);
  void SetVertices(const glm::vec3 &&a, const glm::vec3 &&b, const glm::vec3 &&c, size_t index);
public:
  Sphere();
  ~Sphere();
  void Init();
  void InitBuffers();
  void Draw();
  void Clear();
};
