#pragma once

#include "Screen.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"

class TriangleScreen : public Screen {
  ShaderProgram triangle_program;
  Triangle tri;
public:
  TriangleScreen(Window *win);
  ~TriangleScreen();
  void Init();
  void Display();
  void Keyboard();
  void Clear();
};
