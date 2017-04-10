#include "MenuScreen.hpp"
#include "Storage.hpp"
#include "Window.hpp"
#include "Log.hpp"
#include "UserInterface.hpp"

MenuScreen::MenuScreen(Window *win):
  Screen(win)
{}

MenuScreen::~MenuScreen()
{}

void MenuScreen::Init() {
  UserInterface::Setup(this);
}

void MenuScreen::Display() {
  UserInterface::inst()->Draw();
}

void MenuScreen::Keyboard() {
  if(glfwGetKey(win_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_->window, true);
  } else if(glfwGetKey(win_->window, GLFW_KEY_ENTER) == GLFW_PRESS) {
    should_close = true;
  }
}

void MenuScreen::Mouse(double x, double y) {
}

void MenuScreen::Clear() {
  UserInterface::CleanUp();
}
