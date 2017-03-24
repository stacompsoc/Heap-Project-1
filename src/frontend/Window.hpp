#pragma once

#include <glm/glm.hpp>

#include "incgraphics.h"
#include "Shader.hpp"
#include "Log.hpp"
#include "Sphere.hpp"

class Window {
  GLFWwindow *win_ = NULL;
  size_t width, height;
  ShaderProgram shader_program;
  Sphere sph;

  void start();
  void init_glfw();
  void init_glew();
  void init_controls();
public:
  Window(size_t width, size_t height);
  void gl_version();
  void idle();
  void display();
  void keyboard();
  void clear();
  ~Window();
};
