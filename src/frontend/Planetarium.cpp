#include "Log.hpp"
#include "Planetarium.hpp"

Planetarium::Planetarium()
{}

Planetarium::~Planetarium()
{}

void Planetarium::AddPlanet(Planet &&planet) {
  instance->planets_.push_back(planet);
  planets_.back().Init();
}

void Planetarium::Draw() {
  for(auto &p : planets_) {
    p.Draw();
  }
}

Planetarium *Planetarium::instance = NULL;
Planetarium *Planetarium::inst() {
  return instance;
}

void Planetarium::Setup() {
  ASSERT(instance == NULL);
  instance = new Planetarium();
}

void Planetarium::Clear() {
  ASSERT(instance != NULL);
  while(!instance->planets_.empty()) {
    inst()->planets_.back().Clear();
    inst()->planets_.pop_back();
  }
  delete instance;
  instance = NULL;
}
