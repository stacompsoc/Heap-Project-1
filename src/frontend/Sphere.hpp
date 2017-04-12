#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "VertexArray.hpp"
#include "Shape.hpp"

class Sphere : public Shape {
  VertexArray vao;
  GLuint vert_vbo = 0;
  GLuint tex_vbo = 0;
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
