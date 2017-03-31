#include "MenuScreen.hpp"
#include "Storage.hpp"
#include "Window.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

MenuScreen::MenuScreen(Window *win):
  Screen(win),
  menuprogram({"ptext.vert", "ptext.frag"}),
  text("This is sample text")
{}

MenuScreen::~MenuScreen()
{}

void MenuScreen::Init() {
  size_t ARIAL = Storage::inst()->AddFont("fonts/Arial.ttf");
  menuprogram.Init({"vertex"});
  text.Init(ARIAL);
  projection_matrix = glm::ortho(0.0f, float(width()), 0.0f, float(height()));
}

void MenuScreen::Display() {
  menuprogram.Use();
  u_projection = glGetUniformLocation(menuprogram.id(), "projection");
  glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));
  text.Render(menuprogram, 300.0f, height()/2, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
}

void MenuScreen::Keyboard() {
  if(glfwGetKey(win_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_->window, true);
  }
}

void MenuScreen::Mouse(double x, double y) {
}

void MenuScreen::Clear() {
}
