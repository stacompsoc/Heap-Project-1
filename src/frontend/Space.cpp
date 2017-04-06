#include "Log.hpp"
#include "Space.hpp"

Space::Space(float width, float height):
  cam(width, height),
  planet_program({"planet.vert", "planet.geom", "planet.frag"}),
  skeleton_program({"planet.vert", "planet_skeleton.geom", "planet.frag"})
{}

Space::~Space()
{}

void Space::AddObject(Object &&object) {
  instance->objects_.push_back(object);
  objects_.back().Init();
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

  instance->planet_program.Use(); GLERROR
  Cam()->need_to_update = Cam()->has_changed;
  Cam()->AttachToShader(planet_program);
  Cam()->Update();
  instance->skeleton_program.Use(); GLERROR
  Cam()->AttachToShader(skeleton_program);
  Cam()->Update();
  for(auto &obj : objects_) {
    obj.need_to_update = true;
    obj.Draw();
  }
}

Space *Space::instance = NULL;
Space *Space::inst() {
  return instance;
}

Camera *Space::Cam() {
  return &inst()->cam;
}

void Space::Setup(float width, float height) {
  ASSERT(instance == NULL);
  instance = new Space(width, height);
  instance->planet_program.Init({"vposition", "vtexcoords"});
  instance->skeleton_program.Init({"vposition", "vtexcoords"});
  size_t
    SPHERE = 0,
    RING = 1,
    QUAD = 2;
  size_t
    TEST = Storage::inst()->AddTexture("textures/tester_ring.tga"),
    SUN = Storage::inst()->AddTexture("textures/sun.tga"),
    MERCURY = Storage::inst()->AddTexture("textures/mercury.tga"),
    VENUS = Storage::inst()->AddTexture("textures/venus.tga"),
    EARTH = Storage::inst()->AddTexture("textures/earth.tga"),
    MOON = Storage::inst()->AddTexture("textures/moon.tga"),
    MARS = Storage::inst()->AddTexture("textures/mars.tga"),
    JUPITER = Storage::inst()->AddTexture("textures/jupiter.tga"),
    SATURN = Storage::inst()->AddTexture("textures/saturn.tga"),
    URANUS = Storage::inst()->AddTexture("textures/uranus.tga"),
    NEPTUNE = Storage::inst()->AddTexture("textures/neptune.tga"),
    PLUTO = Storage::inst()->AddTexture("textures/pluto.tga"),
    GERMANY = Storage::inst()->AddTexture("textures/germany.tga"),
    SATURN_RING = Storage::inst()->AddTexture("textures/saturn_ring.tga"),
    URANUS_RING = Storage::inst()->AddTexture("textures/uranus_ring.tga");
  /* float posx = -.95, posy = .95; */
  /* for(size_t i = 0; i < 100; ++i) { */
  /*   double r = float(1 + rand() % 10) / 100.; */
  /*   posx += r + .05; */
  /*   posy -= r + .05; */
  /*   posx = 1.0f - float(rand() % 2000) / 1000.; */
  /*   posy = 1.0f - float(rand() % 2000) / 1000.; */
  /*   float posz = 1.0f - float(rand() % 2000) / 1000.; */
  /*   int texture = SUN + rand() % (GERMANY - SUN); */
  /*   instance->AddObject( */
  /*     Object( */
  /*       SPHERE, */
  /*       instance->planet_program, texture, */
  /*       r, posx,posy,posz, */
  /*       .0001 */
  /*     ) */
  /*   ); */
  /* } */
  float rot = -23.5f;
  float spin = 2.5f;
  instance->AddObject(
    Object(
      SPHERE, instance->planet_program, EARTH,
      1.0f, 0,0,0,
      rot, spin
    )
  );
  /* instance->AddObject( */
  /*   Object( */
  /*     SPHERE, instance->planet_program, SATURN, */
  /*     0.5f, */
  /*     0,0,0, */
  /*     rot */
  /*   ) */
  /* ); */
  /* instance->AddObject( */
  /*   Object( */
  /*     RING, instance->planet_program, SATURN_RING, */
  /*     1.0f, */
  /*     0,0,0, */
  /*     rot */
  /*   ) */
  /* ); */
}

void Space::Clear() {
  ASSERT(instance != NULL);
  Cam()->Clear();
  while(!instance->objects_.empty()) {
    inst()->objects_.back().Clear();
    inst()->objects_.pop_back();
  }
  instance->planet_program.Clear();
  delete instance;
  instance = NULL;
}
