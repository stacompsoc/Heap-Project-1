#pragma once

#include <cstdlib>
#include <bitset>

class Window;

class Screen {
public:
  Screen(Window *win);
  ~Screen();
protected:
  std::bitset <350> key_states;
  Window *win_ = NULL;
  size_t width() const;
  size_t height() const;
  bool key_pressed(int key);
  bool key_hold(int key);
  bool key_released(int key);
  void KeyboardCaller();
public:
  virtual void Init() = 0;
  virtual void Display() = 0;
  virtual void Keyboard() = 0;
  virtual void Mouse(double x, double y) = 0;
  virtual void Clear() = 0;
};
