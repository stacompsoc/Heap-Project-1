#pragma once

#include "Object.hpp"
#include "ShaderProgram.hpp"

#include <glm/glm.hpp>

class MultiObject {
  ShaderProgram &program;
  std::vector <Object> objects;
public:
  MultiObject(ShaderProgram &program);
  ~MultiObject();
  void Init();
  void AddObject(Object &&object);
  void Draw();
  void Clear();
};
