#include "incgraphics.h"
#include "SpaceScreen.hpp"
#include "Planetarium.hpp"
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
  Planetarium::Setup(win_->width(), win_->height());
}

void SpaceScreen::Display() {
  Planetarium::inst()->Draw();
}

void SpaceScreen::Keyboard() {
  Camera *cam = Planetarium::Cam();
  static float accel = 1.01;
  if(glfwGetKey(win_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_->window, true);
  } else if(glfwGetKey(win_->window, GLFW_KEY_UP)) {
    cam->MovePosition(0, -.05, 0);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_DOWN)) {
    cam->MovePosition(0, .05, 0);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_LEFT)) {
    cam->MovePosition(.05, 0, 0);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_RIGHT)) {
    cam->MovePosition(-.05, 0, 0);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_H)) {
    cam->Rotate(0, 1, 0, 10);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_J)) {
    cam->Rotate(1, 0, 0, 10);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_K)) {
    cam->Rotate(1, 0, 0, -10);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_L)) {
    cam->Rotate(0, 1, 0, -10);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_EQUAL)) {
    cam->ChangeScale(1.05);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_MINUS)) {
    cam->ChangeScale(1./1.05);
    cam->Update();
  } else if(glfwGetKey(win_->window, GLFW_KEY_0)) {
    cam->SetScale(1.0f);
    cam->SetPosition(0, 0, .1);
    cam->SetRotation(0, 1, 0, 0);
    cam->Update();
  }
}

void SpaceScreen::Mouse(double x, double y) {
}

void SpaceScreen::Clear() {
  Planetarium::inst()->Clear();
}
