#pragma once

#include "Shape.hpp"

template <int N>
class Ring : public Shape {
protected:
  const int DIM = 60;
  void AddTriangle(
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
