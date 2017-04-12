#include "Space.hpp"
#include "Log.hpp"
#include "Storage.hpp"

Space::Space(float width, float height):
  cam(width, height),
  planetProgram({"planet.vert", "planet.geom", "planet.frag"}),
  skeletonProgram({"planet.vert", "planet_skeleton.geom", "planet.frag"}),
  mainScenerao(this),
  constructor(this)
{}

Space::~Space()
{}

size_t Space::AddMultiObject() {
  if(!spaceObjects.empty()) {
    spaceObjects.back().Init();
  }
  spaceObjects.push_back(MultiObject());
  return spaceObjects.size() - 1;
}

size_t Space::AddObject(Object &&object) {
  ASSERT(!spaceObjects.empty());
  instance->spaceObjects.back().AddObject(object);
  return spaceObjects.back().Size() - 1;
}

void Space::Init() {
  planetProgram.Init({"vposition", "vtexcoords"});
  skeletonProgram.Init({"vposition", "vtexcoords"});
  mainScenerao.Init();
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
  for(size_t i = 0; i < 100; ++i) {
    int texture = SUN + rand() % (SATURN_RING - SUN);
    float r = float(1 + rand() % 10) / 100.;
    float posx = 1.0f - float(rand() % 2000) / 1000.;
    float posy = 1.0f - float(rand() % 2000) / 1000.;
    float posz = 1.0f - float(rand() % 2000) / 1000.;
    float rot = float(rand() % 180 - 90);
    float spin = float(rand() % 20 - 10) / 10;
    constructor.StartObject();
    constructor.SetPosition(posx, posy, posz);
    constructor.SetSize(r);
    constructor.SetRotation(rot);
    constructor.SetSpin(spin);
    constructor.Spawn(Storage::SPHERE, texture, planetProgram);
    if(texture == URANUS || texture == SATURN) {
      int ring = Storage::RING1 + (rand() % 3);
      constructor.SetSize(r / (float(10 - (ring - Storage::RING1 + 2)) / 10.));
      if(texture == SATURN) {
        constructor.Spawn(ring, SATURN_RING, planetProgram);
      } else if(texture == URANUS) {
        constructor.Spawn(ring, URANUS_RING, planetProgram);
      }
    }
    if(texture == EARTH || texture == VENUS) {
      size_t atmotext;
      constructor.SetSize(r * 1.01);
      constructor.SetSpin(spin*1.5);
      if(texture == EARTH) {
        constructor.Spawn(Storage::SPHERE, EARTH_CLOUDS, planetProgram);
      } else if(texture == VENUS) {
        constructor.Spawn(Storage::SPHERE, VENUS_CLOUDS, planetProgram);
      }
    }
  }

  /* constructor.StartObject(); */
  /* constructor.SetRotation(-23.5f); */
  /* constructor.SetSpin(0.1f); */

  /* constructor.SetSize(0.8); */
  /* constructor.Spawn(Storage::SPHERE, EARTH, planetProgram); */
  /* constructor.SetSize(0.81); */
  /* constructor.SetSpin(0.2); */
  /* constructor.Spawn(Storage::SPHERE, EARTH_CLOUDS, planetProgram); */

  /* constructor.SetSize(0.5f); */
  /* constructor.Spawn(Storage::SPHERE, SATURN, planetProgram); */
  /* constructor.SetSize(1.0f); */
  /* constructor.Spawn(Storage::RING3, SATURN_RING, planetProgram); */
}

void Space::Draw() {
  glEnable(GL_DEPTH_CLAMP); GLERROR // disable clipping
  glEnable(GL_DEPTH_TEST); GLERROR
  glDepthFunc(GL_LESS); GLERROR
  glEnable(GL_STENCIL_TEST); GLERROR
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); GLERROR
  glStencilMask(0xFF); GLERROR

  /* glEnable(GL_CULL_FACE); GLERROR // cull face */
  /* glCullFace(GL_BACK); GLERROR // cull back face */
  /* glFrontFace(GL_CW); GLERROR // GL_CCW for counter clock-wise */

  cam.need_to_update = cam.has_changed;
  planetProgram.Use(); GLERROR
  cam.AttachToShader(planetProgram);
  cam.Update();
  skeletonProgram.Use(); GLERROR
  cam.AttachToShader(skeletonProgram);
  cam.Update();
  for(auto &obj : spaceObjects) {
    obj.Draw();
  }
  mainScenerao.Next();
}

void Space::Clear() {
  cam.Clear();
  mainScenerao.Clear();
  while(!spaceObjects.empty()) {
    spaceObjects.back().Clear();
    spaceObjects.pop_back();
  }
  planetProgram.Clear();
  skeletonProgram.Clear();
}

Space *Space::instance = NULL;
Space *Space::inst() {
  return instance;
}

Camera *Space::Cam() {
  return &instance->cam;
}

void Space::Setup(float width, float height) {
  ASSERT(instance == NULL);
  instance = new Space(width, height);
  instance->Init();
}

void Space::Cleanup() {
  ASSERT(instance != NULL);
  instance->Clear();
  delete instance;
  instance = NULL;
}
