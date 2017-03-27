#pragma once

#include <glm/glm.hpp>

#include "incgraphics.h"
#include "Planetarium.hpp"
#include "Shader.hpp"
#include "Log.hpp"
#include "PlanetariumScreen.hpp"
#include "TriangleScreen.hpp"

class Window {
  size_t width_, height_;

  PlanetariumScreen planetscreen;
  TriangleScreen trianglescreen;
  Screen *current_screen;

  void start();
  void init_glfw();
  void init_glew();
  void init_controls();
public:
  GLFWwindow *window = NULL;
  Window(size_t width, size_t height);
  size_t width() const;
  size_t height() const;
  void GLVersion();
  void Init();
  void Idle();
  void Display();
  void Keyboard();
  void Clear();
  ~Window();
};
