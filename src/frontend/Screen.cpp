#include "Screen.hpp"
#include "Debug.hpp"
#include "Window.hpp"

Screen::Screen(gl::Window *win):
  win_(win)
{}

Screen::~Screen()
{}

void Screen::Resize() {
}

void Screen::Keyboard() {
}

void Screen::KeyPress(int key, int scancode, int mods) {
}

void Screen::KeyRelease(int key, int scancode, int mods) {
}

void Screen::MouseScroll(double xoffset, double yoffset) {
}

size_t Screen::width() const {
  return win_->width();
}

size_t Screen::height() const {
  return win_->height();
}
