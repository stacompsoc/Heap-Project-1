#pragma once

#include "Shape.hpp"

class Sphere : public Shape {
protected:
  const int DIM = 15;
  void AddTriangle(
    const glm::vec3 &a,
    const glm::vec3 &b,
    const glm::vec3 &c,
    size_t index,
    bool is_textured = false
  );
public:
  Sphere();
  ~Sphere();
  void Init();
  using Shape::Draw;
  using Shape::Clear;
};
