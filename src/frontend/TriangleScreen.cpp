#include "TriangleScreen.hpp"
#include "Log.hpp"
#include "Shader.hpp"
#include "Window.hpp"

TriangleScreen::TriangleScreen(Window *win):
  Screen(win),
  triangle_program("triangle.vert", "triangle.geom", "triangle.frag"),
  tri()
{}

TriangleScreen::~TriangleScreen()
{}

void TriangleScreen::Init() {
  GLfloat position[] = {
    -0.5, -0.5, 0.0,
    0.0, 0.5, 0.0,
    0.5, -0.5, 0.0,
  };
  tri.Init(position, 0);
  triangle_program.Init({"vposition", "vcolor"});
}

void TriangleScreen::Display() {
  triangle_program.Use();
  tri.Draw();
}

void TriangleScreen::Keyboard() {
  if(glfwGetKey(win_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_->window, true);
  }
}

void TriangleScreen::Clear() {
  tri.Clear();
  triangle_program.Clear();
}
