#pragma once

#include "Screen.hpp"

class Window;

class MenuScreen : public Screen {
  const char *background = "background.tga";
public:
  MenuScreen(Window *win);
  ~MenuScreen();
  void Init();
  void Display();
  void Keyboard();
  void Clear();
};
