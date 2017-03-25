#include "Planet.hpp"

Planet::Planet(Sphere &&body):
  body(body)
{}

Planet::~Planet()
{}

void Planet::Init() {
  body.Init();
}

void Planet::Draw() {
  body.Draw();
}

void Planet::Clear() {
  body.Clear();
}
