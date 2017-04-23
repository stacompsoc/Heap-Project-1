#pragma once

#include <glm/glm.hpp>
#include "Shape.hpp"
#include "Triangle.hpp"

class Quad : public Shape {
protected:
  std::vector <Triangle> triangles;
  void SetTexcoords(size_t index, GLfloat texcoords[6]);
  void AddTriangle(
    const glm::vec3 &a,
    const glm::vec3 &b,
    const glm::vec3 &c,
    size_t index,
    bool is_textured = false
  );
public:
  Quad();
  ~Quad();
  void Init();
  void Draw();
  void Clear();
};
