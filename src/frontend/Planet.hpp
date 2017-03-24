#pragma once

#include "Sphere.hpp"

class Planet {
  Sphere body;
public:
  Planet(Sphere &&body);
  ~Planet();
  virtual void Init();
  virtual void Draw();
  virtual void Clear();
};
