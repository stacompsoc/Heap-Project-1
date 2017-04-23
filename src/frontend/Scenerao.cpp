#include "Scenerao.hpp"
#include "Storage.hpp"
#include "Space.hpp"
#include "Log.hpp"

Scenerao::Scenerao(Space *space):
  space(space)
{}

Scenerao::~Scenerao()
{}

void Scenerao::Init() {
  size_t
    EARTH_CLOUDS = Storage::AddTexture("textures/earth_clouds.png"),
    VENUS_CLOUDS = Storage::AddTexture("textures/venus_clouds.png"),
    SUN = Storage::AddTexture("textures/sun.png"),
    MERCURY = Storage::AddTexture("textures/mercury.png"),
    VENUS = Storage::AddTexture("textures/venus.png"),
    EARTH = Storage::AddTexture("textures/earth.png"),
    MOON = Storage::AddTexture("textures/moon.png"),
    MARS = Storage::AddTexture("textures/mars.png"),
    JUPITER = Storage::AddTexture("textures/jupiter.png"),
    SATURN = Storage::AddTexture("textures/saturn.png"),
    URANUS = Storage::AddTexture("textures/uranus.png"),
    NEPTUNE = Storage::AddTexture("textures/neptune.png"),
    PLUTO = Storage::AddTexture("textures/pluto.png"),
    SATURN_RING = Storage::AddTexture("textures/saturn_ring.png"),
    URANUS_RING = Storage::AddTexture("textures/uranus_ring.png"),
    TEST = Storage::AddTexture("textures/tester_ring.png");
  for(size_t i = 0; i < 1000; ++i) {
    int texture = SUN + rand() % (SATURN_RING - SUN);
    float r = float(1 + rand() % 10) / 100.;
    float posx = 1.0f - float(rand() % 2000) / 1000.;
    float posy = 1.0f - float(rand() % 2000) / 1000.;
    float posz = 1.0f - float(rand() % 2000) / 1000.;
    float rot = float(rand() % 180 - 90);
    float spin = float(rand() % 20 - 10) / 10;
    space->constructor.StartObject();
    space->constructor.SetPosition(posx, posy, posz);
    space->constructor.SetSize(r);
    space->constructor.SetRotation(rot);
    space->constructor.SetSpin(spin);
    space->constructor.Spawn(Storage::SPHERE, texture, space->planetProgram);
    if(texture == URANUS || texture == SATURN) {
      if(texture == SATURN) {
        int ring = Storage::RING3;
        space->constructor.SetSize(r / (float(10 - (ring - Storage::RING1 + 2)) / 10.));
        space->constructor.Spawn(ring, SATURN_RING, space->planetProgram);
      } else if(texture == URANUS) {
        int ring = Storage::RING1;
        space->constructor.SetSize(r / (float(10 - (ring - Storage::RING1 + 2)) / 10.));
        space->constructor.Spawn(ring, URANUS_RING, space->planetProgram);
      }
    }
    if(texture == EARTH || texture == VENUS) {
      size_t atmotext;
      space->constructor.SetSize(r * 1.01);
      space->constructor.SetSpin(spin*1.5);
      if(texture == EARTH) {
        space->constructor.Spawn(Storage::SPHERE, EARTH_CLOUDS, space->planetProgram);
      } else if(texture == VENUS) {
        space->constructor.Spawn(Storage::SPHERE, VENUS_CLOUDS, space->planetProgram);
      }
    }
  }

  /* space->constructor.StartObject(); */
  /* space->constructor.SetRotation(-23.5f); */
  /* space->constructor.SetSpin(0.1f); */

  /* space->constructor.SetSize(0.8); */
  /* space->constructor.Spawn(Storage::SPHERE, EARTH, space->planetProgram); */
  /* space->constructor.SetSize(0.81); */
  /* space->constructor.SetSpin(0.2); */
  /* space->constructor.Spawn(Storage::SPHERE, EARTH_CLOUDS, space->planetProgram); */

  /* space->constructor.SetSize(0.5f); */
  /* space->constructor.Spawn(Storage::SPHERE, SATURN, space->planetProgram); */
  /* space->constructor.SetSize(1.0f); */
  /* space->constructor.Spawn(Storage::RING3, SATURN_RING, space->planetProgram); */
}

void Scenerao::Next() {
}

void Scenerao::Clear() {
}
