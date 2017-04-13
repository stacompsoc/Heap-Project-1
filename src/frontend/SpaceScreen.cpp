#include "incgraphics.h"
#include "SpaceScreen.hpp"
#include "Space.hpp"
#include "Camera.hpp"
#include "Log.hpp"
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
  Space::Setup(win_->width(), win_->height());
}

void SpaceScreen::Display() {
  Space::inst()->Draw();
}

void SpaceScreen::Keyboard() {
  Camera *cam = Space::Cam();
  static float accel = 1.01;
  if(glfwGetKey(win_->window, GLFW_KEY_ENTER) == GLFW_PRESS) {
    /* should_close = true; */
  } else if(glfwGetKey(win_->window, GLFW_KEY_UP)) {
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

void SpaceScreen::Mouse(double x, double y) {
}

void SpaceScreen::Clear() {
  Space::Cleanup();
}
