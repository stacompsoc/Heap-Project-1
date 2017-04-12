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
