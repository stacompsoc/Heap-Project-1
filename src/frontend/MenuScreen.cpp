#include "MenuScreen.hpp"
#include "UserInterface.hpp"
#include "Window.hpp"
#include "Debug.hpp"

MenuScreen::MenuScreen(gl::Window *win):
  Screen(win)
{}

MenuScreen::~MenuScreen()
{}

void MenuScreen::Init() {
  UserInterface::Setup(this);
}

void MenuScreen::Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); GLERROR
  UserInterface::inst()->Draw();
}

void MenuScreen::Keyboard() {
}

void MenuScreen::KeyPress(int key, int scancode, int mods) {
  if(key == GLFW_KEY_ENTER)
    should_close = true;
}

void MenuScreen::Mouse(double x, double y) {
}

void MenuScreen::Clear() {
  UserInterface::CleanUp();
}
