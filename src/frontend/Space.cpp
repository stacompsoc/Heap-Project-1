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
    SUN = Storage::AddTexture("textures/sun.tga"),
    MERCURY = Storage::AddTexture("textures/mercury.tga"),
    VENUS = Storage::AddTexture("textures/venus.tga"),
    EARTH = Storage::AddTexture("textures/earth.tga"),
    MOON = Storage::AddTexture("textures/moon.tga"),
    MARS = Storage::AddTexture("textures/mars.tga"),
    JUPITER = Storage::AddTexture("textures/jupiter.tga"),
    SATURN = Storage::AddTexture("textures/saturn.tga"),
    URANUS = Storage::AddTexture("textures/uranus.tga"),
    NEPTUNE = Storage::AddTexture("textures/neptune.tga"),
    PLUTO = Storage::AddTexture("textures/pluto.tga"),
    SATURN_RING = Storage::AddTexture("textures/saturn_ring.tga"),
    URANUS_RING = Storage::AddTexture("textures/uranus_ring.tga"),
    TEST = Storage::AddTexture("textures/tester_ring.tga");
  for(size_t i = 0; i < 1000; ++i) {
    int texture = SUN + rand() % (SATURN_RING - SUN);
    float r = float(1 + rand() % 10) / 100.;
    float posx = 3.0f - float(rand() % 6000) / 1000.;
    float posy = 3.0f - float(rand() % 6000) / 1000.;
    float posz = 3.0f - float(rand() % 6000) / 1000.;
    float rot = float(rand() % 180 - 90);
    float spin = float(rand() % 20 - 10) / 10;
    constructor.StartObject();
    constructor.SetPosition(posx, posy, posz);
    constructor.SetSize(r);
    constructor.SetRotation(rot);
    constructor.SetSpin(spin);
    constructor.Spawn(Storage::SPHERE, texture, planetProgram);
    if(rand() % 3 == 0) {
      int ring = Storage::RING1 + (rand() % 3);
      int ringtex = SATURN_RING + (rand() % (TEST - SATURN_RING));
      constructor.SetSize(r / (float(10 - (ring - Storage::RING1 + 2)) / 10.));
      constructor.Spawn(ring, ringtex, planetProgram);
    }
  }

  /* constructor.StartObject(); */
  /* constructor.SetRotation(-23.5f); */
  /* constructor.SetSpin(2.5f); */

  /* constructor.SetSize(1.0); */
  /* constructor.Spawn(Storage::SPHERE, EARTH, planetProgram); */

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
