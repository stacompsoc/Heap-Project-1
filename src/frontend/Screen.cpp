#include "Screen.hpp"
#include "Window.hpp"

Screen::Screen(Window *win):
  win_(win)
{}

Screen::~Screen()
{}

size_t Screen::width() const {
  return win_->width();
}

size_t Screen::height() const {
  return win_->height();
}
