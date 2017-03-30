#pragma once

#include "Triangle.hpp"

class Shape {
protected:
  std::vector <Triangle> triangles;
public:
  Shape();
  virtual ~Shape();
  virtual void Init() = 0;
  virtual void Draw();
  virtual void Clear();
};
