#include "Log.hpp"
#include "Planetarium.hpp"

Planetarium::Planetarium(float width, float height):
  cam(width, height)
{}

Planetarium::~Planetarium()
{}

void Planetarium::AddObject(Object &&object) {
  instance->objects_.push_back(object);
  objects_.back().Init();
}

void Planetarium::Draw() {
  Cam()->Update();
  for(auto &obj : objects_) {
    obj.Draw();
  }
}

Planetarium *Planetarium::instance = NULL;
Planetarium *Planetarium::inst() {
  return instance;
}

Camera *Planetarium::Cam() {
  return &inst()->cam;
}

void Planetarium::Setup(float width, float height) {
  ASSERT(instance == NULL);
  instance = new Planetarium(width, height);
}

void Planetarium::Clear() {
  ASSERT(instance != NULL);
  Cam()->Clear();
  while(!instance->objects_.empty()) {
    inst()->objects_.back().Clear();
    inst()->objects_.pop_back();
  }
  delete instance;
  instance = NULL;
}
