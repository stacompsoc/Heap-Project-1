#pragma once

#include <glm/glm.hpp>
#include "Shape.hpp"
#include "Triangle.hpp"

template <int N>
class Ring : public Shape {
protected:
  GLuint vao = 0;
  GLuint vert_vbo = 0;
  GLuint tex_vbo = 0;
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
