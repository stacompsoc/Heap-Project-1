#include "incgraphics.h"
#include "SpaceScreen.hpp"
#include "Space.hpp"
#include "Camera.hpp"
#include "Debug.hpp"
#include "Window.hpp"
#include "Object.hpp"
#include "Sphere.hpp"

#include <glm/glm.hpp>

SpaceScreen::SpaceScreen(Window *win):
  Screen(win)
{}

SpaceScreen::~SpaceScreen()
{}

void SpaceScreen::Init() {
  Space::Setup();
}

void SpaceScreen::Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); GLERROR
  Space::inst()->Draw();
}

void SpaceScreen::Resize() {
  Space::Cam()->WindowResized(width(), height());
}

void SpaceScreen::Keyboard() {
  Camera *cam = Space::Cam();
  static float accel = 1.01;
  if(glfwGetKey(win_->window, GLFW_KEY_UP)) {
    cam->MovePosition(0, -.05, 0);
  } else if(glfwGetKey(win_->window, GLFW_KEY_DOWN)) {
    cam->MovePosition(0, .05, 0);
  } else if(glfwGetKey(win_->window, GLFW_KEY_LEFT)) {
    cam->MovePosition(.05, 0, 0);
  } else if(glfwGetKey(win_->window, GLFW_KEY_RIGHT)) {
    cam->MovePosition(-.05, 0, 0);
  } else if(glfwGetKey(win_->window, GLFW_KEY_W)) {
    cam->Rotate(1, 0, 0, 10);
  } else if(glfwGetKey(win_->window, GLFW_KEY_S)) {
    cam->Rotate(1, 0, 0, -10);
  } else if(glfwGetKey(win_->window, GLFW_KEY_A)) {
    cam->Rotate(0, 1, 0, 10);
  } else if(glfwGetKey(win_->window, GLFW_KEY_D)) {
    cam->Rotate(0, 1, 0, -10);
  } else if(glfwGetKey(win_->window, GLFW_KEY_Q)) {
    cam->Rotate(0, 0, 1, 10);
  } else if(glfwGetKey(win_->window, GLFW_KEY_E)) {
    cam->Rotate(0, 0, 1, -10);
  } else if(glfwGetKey(win_->window, GLFW_KEY_EQUAL)) {
    cam->Scale(1.05);
  } else if(glfwGetKey(win_->window, GLFW_KEY_MINUS)) {
    cam->Scale(1./1.05);
  } else if(glfwGetKey(win_->window, GLFW_KEY_0)) {
    cam->SetScale(1.0f);
    cam->SetPosition(0, 0, .1);
    cam->SetRotation(0, 1, 0, 0);
  }
}

void SpaceScreen::KeyPress(int key, int scancode, int mods) {
  if(key == GLFW_KEY_ENTER)
    should_close = true;
}

void SpaceScreen::Mouse(double x, double y) {
}

void SpaceScreen::MouseScroll(double xoffset, double yoffset) {
  Space::Cam()->Rotate(0, 1, 0, xoffset * 2);
  Space::Cam()->Rotate(1, 0, 0, yoffset * 2);
}

void SpaceScreen::Clear() {
  Space::Cleanup();
}
