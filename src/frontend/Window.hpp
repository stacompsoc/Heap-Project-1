#pragma once

#include <glm/glm.hpp>

#include "incgraphics.h"
#include "Planetarium.hpp"
#include "Shader.hpp"
#include "Log.hpp"

class Window {
  GLFWwindow *win_ = NULL;
  size_t width, height;
  ShaderProgram shader_program;

  void start();
  void init_glfw();
  void init_glew();
  void init_controls();
public:
  Window(size_t width, size_t height);
  void GLVersion();
  void Idle();
  void Display();
  void Keyboard();
  void Clear();
  ~Window();
};
