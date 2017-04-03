#pragma once

#include "Screen.hpp"
#include "ShaderProgram.hpp"
#include "Object.hpp"

class SpaceScreen : public Screen {
public:
  SpaceScreen(Window *win);
  ~SpaceScreen();
  void Init();
  void Display();
  void Keyboard();
  void Mouse(double x, double y);
  void Clear();
};
