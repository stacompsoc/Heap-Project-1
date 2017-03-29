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
  Screen(win),
  planet_program("planet.vert", "planet.geom", "planet.frag")
{}

SpaceScreen::~SpaceScreen()
{}

void SpaceScreen::Init() {
  Planetarium::Setup(win_->width(), win_->height());
  /* Planetarium::inst()->AddPlanet(Sphere(glm::vec3(0.0f, 0.0f, 0.0f), .3)); */
  Planetarium::inst()->AddObject(
    Object(
      *Storage::inst()->shapes()[0],
      planet_program
    )
  );
  planet_program.Init({"vposition", "vcolor"});
  Storage::inst()->AddTexture("example.tga");
  /* Storage::inst()->AddShape<Sphere>(); */
}

void SpaceScreen::Display() {
  Planetarium::Cam()->AttachToShader(planet_program);
  planet_program.Use(); GLERROR
  Planetarium::inst()->Draw();
}

void SpaceScreen::Keyboard() {
  Camera *cam = Planetarium::Cam();
  if(glfwGetKey(win_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_->window, true);
  } else if(glfwGetKey(win_->window, GLFW_KEY_UP)) {
    cam->yx -= M_PI / 10.;
  } else if(glfwGetKey(win_->window, GLFW_KEY_DOWN)) {
    cam->yx += M_PI / 10.;
  } else if(glfwGetKey(win_->window, GLFW_KEY_LEFT)) {
    cam->zx -= M_PI/10.;
  } else if(glfwGetKey(win_->window, GLFW_KEY_RIGHT)) {
    cam->zx += M_PI/10.;
  } else if(glfwGetKey(win_->window, GLFW_KEY_EQUAL)) {
    cam->dist *= 1.05;
  } else if(glfwGetKey(win_->window, GLFW_KEY_MINUS)) {
    cam->dist /= 1.05;
  } else if(glfwGetKey(win_->window, '0')) {
    cam->dist = 1., cam->zx = 0., cam->yx = M_PI/2.;
  }
  cam->Update();
}

void SpaceScreen::Clear() {
  Planetarium::inst()->Clear();
  planet_program.Clear();
}
