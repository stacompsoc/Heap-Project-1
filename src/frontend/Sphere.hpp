#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "incgraphics.h"
#include "Triangle.hpp"

class Sphere {
  glm::vec3 position;
  GLfloat radius;
  std::vector <Triangle> tessellation;
  void add_triangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, size_t color);
public:
  Sphere(glm::vec3 position, GLfloat r);
  ~Sphere();
  void Init();
  void Draw();
  void Clear();
};
