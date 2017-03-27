#include "MenuScreen.hpp"
#include "Sprite.hpp"
#include "Window.hpp"
#include "Log.hpp"

MenuScreen::MenuScreen(Window *win):
  Screen(win)
{}

MenuScreen::~MenuScreen()
{}

void MenuScreen::Init() {
  /* Sprite::inst()->AddTexture("example.tga"); */
  /* Sprite::inst()->AddTexture("background.tga"); */
}

void MenuScreen::Display() {
}

void MenuScreen::Keyboard() {
}

void MenuScreen::Clear() {
}
