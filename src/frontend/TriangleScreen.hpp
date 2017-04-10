#pragma once

#include "Screen.hpp"
#include "ShaderProgram.hpp"
#include "Triangle.hpp"

class TriangleScreen : public Screen {
  ShaderProgram triangle_program;
  Triangle tri;
  size_t tex_idx = 1e9;
public:
  TriangleScreen(Window *win);
  ~TriangleScreen();
  void Init();
  void Display();
  void Keyboard();
  void Mouse(double x, double y);
  void Clear();
};
