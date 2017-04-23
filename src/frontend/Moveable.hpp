#pragma once

#include <glm/glm.hpp>

class Moveable {
protected:
  glm::mat4
    translate,
    rotate,
    scale;
public:
  bool has_changed = true;
  void Scale(float scaling);
  void Scale(float sx, float sy, float sz);
  void SetScale(float scaling);
  void SetScale(float sx, float sy, float sz);
  void Rotate(float x, float y, float z, float deg);
  void SetRotation(float x, float y, float z, float deg);
  void SetPosition(float x, float y, float z);
  void MovePosition(float x, float y, float z);
};
