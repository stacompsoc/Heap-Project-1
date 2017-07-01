#pragma once

#include <map>
#include <glm/glm.hpp>

#include "incgraphics.h"
#include "Audio.hpp"
#include "MenuScreen.hpp"
#include "SpaceScreen.hpp"
#include "TriangleScreen.hpp"

namespace gl {
class Window {
protected:
  size_t width_, height_;

  al::Audio audio;
  MenuScreen menuscreen;
  SpaceScreen spacescreen;
  TriangleScreen trianglescreen;
  Screen *current_screen;

  void start();
  void init_glfw();
  void init_glew();
  void init_controls();
  const GLFWvidmode *vidmode = NULL;
public:
  GLFWwindow *window = NULL;
  Window();
  ~Window();
  size_t width() const;
  size_t height() const;
  void GLVersion();
  void Init();
  void Idle();
  void Display();
  void Resize(float new_width, float new_height);
  void Switch();
  void Keyboard();
  void KeyboardEvent(int key, int scancode, int action, int mods);
  void Mouse(double x, double y);
  void MouseClick(double x, double y, int button, int action, int mods);
  void MouseScroll(double xoffset, double yoffset);
  void Clear();
};

extern std::map <GLFWwindow *, Window *> window_reference;
}

namespace glfw {
void error_callback(int error, const char* description);
void keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void size_callback(GLFWwindow *window, int new_width, int new_height);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
}
