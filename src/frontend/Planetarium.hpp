#pragma once

#include <vector>

#include "Planet.hpp"

class Planetarium {
  std::vector <Planet> planets_;
  static Planetarium *instance;
public:
  Planetarium();
  ~Planetarium();
  void AddPlanet(Planet &&planet);
  void Draw();
  static Planetarium *inst();
  static void Setup();
  static void Clear();
};
