#pragma once

#include "Screen.hpp"
#include "ShaderProgram.hpp"
#include "Triangle.hpp"

class TriangleScreen : public Screen {
  gl::ShaderProgram triangle_program;
  gl::Triangle tri;
  size_t tex_idx = 1e9;
public:
  TriangleScreen(gl::Window *win);
  ~TriangleScreen();
  void Init();
  void Display();
  void Keyboard();
  void Mouse(double x, double y);
  void Clear();
};
