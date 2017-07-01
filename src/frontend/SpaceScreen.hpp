#pragma once

#include "Screen.hpp"
#include "ShaderProgram.hpp"
#include "Object.hpp"

class SpaceScreen : public Screen {
public:
  SpaceScreen(gl::Window *win);
  ~SpaceScreen();
  void Init();
  void Display();
  void Resize();
  void Keyboard();
  void KeyPress(int key, int scancode, int mods);
  void Mouse(double x, double y);
  void MouseScroll(double xoffset, double yoffset);
  void Clear();
};
