#pragma once

#include <glm/glm.hpp>

class UserInterface;

class UIBuilder {
  UserInterface *ui;
  glm::vec2 size;
  glm::vec2 position;
  size_t font = 0;
public:
  UIBuilder(UserInterface *ui);
  ~UIBuilder();
  void Resize(float s);
  void Resize(float x, float y);
  void SetSize(float s);
  void SetSize(float x, float y);
  void Move(float x, float y);
  void SetPosition(float x, float y);
};
