#pragma once

#include <cstdlib>

namespace gl {
class Window;
}

class Screen {
public:
  Screen(gl::Window *win);
  ~Screen();
  size_t width() const;
  size_t height() const;
protected:
  gl::Window *win_ = NULL;
public:
  bool should_close = false;
  virtual void Init() = 0;
  virtual void Display() = 0;
  virtual void Resize();
  virtual void Keyboard();
  virtual void KeyPress(int key, int scancode, int mods);
  virtual void KeyRelease(int key, int scancode, int mods);
  virtual void Mouse(double x, double y) = 0;
  virtual void MouseScroll(double xoffset, double yoffset);
  virtual void Clear() = 0;
};
