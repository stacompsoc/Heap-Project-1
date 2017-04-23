#pragma once

#include "Screen.hpp"

class Window;

class MenuScreen : public Screen {
public:
  MenuScreen(Window *win);
  ~MenuScreen();
  void Init();
  void Display();
  void Keyboard();
  void KeyPress(int key, int scancode, int mods);
  void Mouse(double x, double y);
  void Clear();
};
