#pragma once

#include <cstdlib>

class Window;

class Screen {
public:
  Screen(Window *win);
  ~Screen();
protected:
  Window *win_ = NULL;
  size_t width() const;
  size_t height() const;
public:
  virtual void Init() = 0;
  virtual void Display() = 0;
  virtual void Keyboard() = 0;
  virtual void Clear() = 0;
};
