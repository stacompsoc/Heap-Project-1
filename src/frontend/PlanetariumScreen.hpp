#pragma once

#include "Screen.hpp"
#include "Shader.hpp"

class PlanetariumScreen : public Screen {
  ShaderProgram planet_program;
public:
  PlanetariumScreen(Window *win);
  ~PlanetariumScreen();
  void Init();
  void Display();
  void Keyboard();
  void Clear();
};
