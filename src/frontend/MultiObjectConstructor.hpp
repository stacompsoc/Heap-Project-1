#pragma once

#include <glm/glm.hpp>
#include "ShaderProgram.hpp"

class Space;

class MultiObjectConstructor {
  Space *space;
  glm::vec3 position;
  glm::vec3 size;
  float rot = 0;
  float spin = 0;
public:
  MultiObjectConstructor(Space *space);
  ~MultiObjectConstructor();
  void Move(float x, float y, float z);
  void SetPosition(float x, float y, float z);
  void SetSize(float s);
  void SetSize(float x, float y, float z);
  void SetRotation(float r);
  void SetSpin(float s);
  void Spawn(size_t shape_id, size_t texture_id, ShaderProgram &program);
  void StartObject();
};
