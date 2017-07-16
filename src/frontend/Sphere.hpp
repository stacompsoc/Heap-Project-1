#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "Shape.hpp"
#include "VertexArray.hpp"
#include "ShaderAttrib.hpp"

class Sphere : public Shape {
  gl::VertexArray vao;
  gl::Attrib vert, tex;
  GLfloat
    *vertices = NULL,
    *txcoords = NULL;
protected:
  static const size_t DIM;
  static const size_t SIZE;
public:
  Sphere();
  ~Sphere();
  void Init();
  void Draw();
  void Clear();
};
