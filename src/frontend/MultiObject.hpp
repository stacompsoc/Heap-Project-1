#pragma once

#include "Object.hpp"

#include <functional>
#include <glm/glm.hpp>

class MultiObject {
  std::vector <Object> objects;
public:
  MultiObject();
  ~MultiObject();
  size_t Size() const;
  void AddObject(Object object);
  void Apply(std::function <void (Object &)> &&func);
  void Init();
  void Draw();
  void Scale(float s);
  void SetScale(float s);
  void Rotate(float x, float y, float z, float deg);
  void RotateAxis();
  void MovePosition(float x, float y, float z);
  void SetPosition(float x, float y, float z);
  void Clear();
};
