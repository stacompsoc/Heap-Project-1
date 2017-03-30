#pragma once

#include "Screen.hpp"
#include "Shader.hpp"
#include "Object.hpp"

class SpaceScreen : public Screen {
public:
  SpaceScreen(Window *win);
  ~SpaceScreen();
  void Init();
  void Display();
  void Keyboard();
  void Clear();
};
