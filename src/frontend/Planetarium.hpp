#pragma once

#include <vector>

#include "Camera.hpp"
#include "Object.hpp"

class Planetarium {
  std::vector <Object> objects_;
  static Planetarium *instance;
  Planetarium(float width, float height);
  ~Planetarium();
  Camera cam;
public:
  void AddObject(Object &&object);
  void Draw();
  static Planetarium *inst();
  static Camera *Cam();
  static void Setup(float width, float height);
  static void Clear();
};
