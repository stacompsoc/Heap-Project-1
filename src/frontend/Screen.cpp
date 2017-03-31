#include "Screen.hpp"
#include "Window.hpp"
#include "Log.hpp"

Screen::Screen(Window *win):
  win_(win), key_states()
{}

Screen::~Screen()
{}

bool Screen::key_pressed(int key) {
  ASSERT(win_ != NULL);
  bool ret = glfwGetKey(win_->window, key) == GLFW_PRESS;
  if(ret && !key_states[key]) {
    key_states[key] = true;
    return true;
  }
  return false;
}

bool Screen::key_hold(int key) {
  ASSERT(win_ != NULL);
  return glfwGetKey(win_->window, key);
}

bool Screen::key_released(int key) {
  ASSERT(win_ != NULL);
  bool ret = glfwGetKey(win_->window, key) == GLFW_RELEASE;
  if(ret)
    key_states[key] = false;
  return ret;
}

size_t Screen::width() const {
  return win_->width();
}

size_t Screen::height() const {
  return win_->height();
}
