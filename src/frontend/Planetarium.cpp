#include "Log.hpp"
#include "Planetarium.hpp"

Planetarium::Planetarium()
{}

Planetarium::~Planetarium()
{}

void Planetarium::AddPlanet(Planet &&planet) {
  inst()->planets_.push_back(planet);
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
  ASSERT(inst() == NULL);
  instance = new Planetarium();
}

void Planetarium::Clear() {
  while(!inst()->planets_.empty()) {
    inst()->planets_.back().Clear();
    inst()->planets_.pop_back();
  }
}
