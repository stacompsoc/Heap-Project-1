#pragma once

#include "Shape.hpp"

class Ring : public Shape {
protected:
  const int DIM = 10;
  glm::vec3 position;
  double angle_yx, angle_zx;
  void add_triangle(
    const glm::vec3 &a,
    const glm::vec3 &b,
    const glm::vec3 &c,
    size_t index,
    bool is_textured = false
  );
public:
  Ring();
  ~Ring();
  void Init();
  using Shape::Draw;
  using Shape::Clear;
};
