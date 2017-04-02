#pragma once

#include "Triangle.hpp"

class Shape {
protected:
  std::vector <Triangle> triangles;
  virtual void AddTriangle(
    const glm::vec3 &a,
    const glm::vec3 &b,
    const glm::vec3 &c,
    size_t index,
    bool is_textured = false
  ) = 0;
public:
  Shape();
  virtual ~Shape();
  virtual void Init() = 0;
  virtual void Draw();
  virtual void Clear();
};
