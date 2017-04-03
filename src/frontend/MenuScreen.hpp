#pragma once

#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Screen.hpp"
#include "Texture.hpp"
#include "Text.hpp"
#include "Object.hpp"

#include <vector>
#include <glm/glm.hpp>

class Window;

class MenuScreen : public Screen {
protected:
  ShaderProgram quadprogram;
  ShaderProgram menuprogram;
  Text text;
  /* Text label; */
  size_t PIC, BTN, BTNSEL;
  std::vector <Object> objects;
  Uniform<MAT4>u_proj;
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
