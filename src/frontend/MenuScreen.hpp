#pragma once

#include "Shader.hpp"
#include "Screen.hpp"
#include "Text.hpp"

#include <glm/glm.hpp>

class Window;

class MenuScreen : public Screen {
protected:
  ShaderProgram menuprogram;
  Text text;
  GLuint u_projection;
  glm::mat4 projection_matrix;
public:
  MenuScreen(Window *win);
  ~MenuScreen();
  void Init();
  void Display();
  void Keyboard();
  void Mouse(double x, double y);
  void Clear();
};
