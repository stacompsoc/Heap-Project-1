#include "MenuScreen.hpp"
#include "Storage.hpp"
#include "Window.hpp"
#include "Log.hpp"

MenuScreen::MenuScreen(Window *win):
  Screen(win)
{}

MenuScreen::~MenuScreen()
{}

void MenuScreen::Init() {
  /* Storage::inst()->AddTexture("example.tga"); */
  /* Storage::inst()->AddTexture("background.tga"); */
}

void MenuScreen::Display() {
}

void MenuScreen::Keyboard() {
}

void MenuScreen::Clear() {
}
