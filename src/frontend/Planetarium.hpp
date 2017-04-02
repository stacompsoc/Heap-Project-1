#pragma once

#include <vector>

#include "Camera.hpp"
#include "Object.hpp"
#include "ShaderProgram.hpp"

class Planetarium {
  ShaderProgram planet_program;
  ShaderProgram skeleton_program;
  ShaderProgram glow_program;
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
