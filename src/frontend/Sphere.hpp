#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "incgraphics.h"

#include "Triangle.hpp"
#include "Object.hpp"

class Sphere : public Shape {
protected:
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
  GLfloat radius;
  void add_triangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, size_t color);
public:
  Sphere();
  Sphere(glm::vec3 position, GLfloat r);
  ~Sphere();
  void Init();
  using Shape::Draw;
  using Shape::Clear;
};
