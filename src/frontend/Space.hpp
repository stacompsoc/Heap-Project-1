#pragma once

#include <vector>

#include "Camera.hpp"
#include "Object.hpp"
#include "ShaderProgram.hpp"

class Space {
  ShaderProgram planet_program;
  ShaderProgram skeleton_program;
  std::vector <Object> objects_;
  static Space *instance;
  Space(float width, float height);
  ~Space();
  Camera cam;
public:
  void AddObject(Object &&object);
  void Draw();
  static Space *inst();
  static Camera *Cam();
  static void Setup(float width, float height);
  static void Clear();
};
