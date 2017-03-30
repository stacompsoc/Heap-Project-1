#include "Log.hpp"
#include "Planetarium.hpp"

Planetarium::Planetarium(float width, float height):
  cam(width, height),
  planet_program("planet.vert", "planet.geom", "planet.frag")
{}

Planetarium::~Planetarium()
{}

void Planetarium::AddObject(Object &&object) {
  instance->objects_.push_back(object);
  objects_.back().Init();
}

void Planetarium::Draw() {
  Cam()->AttachToShader(planet_program);
  instance->planet_program.Use(); GLERROR
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
  instance->planet_program.Init({"vposition", "vtexcoords"});
  size_t
    SUN = Storage::inst()->AddTexture("textures/sun.tga"),
    MERCURY = Storage::inst()->AddTexture("textures/mercury.tga"),
    VENUS = Storage::inst()->AddTexture("textures/venus.tga"),
    EARTH = Storage::inst()->AddTexture("textures/earth.tga"),
    /* MOON = Storage::inst()->AddTexture("textures/moon.tga"), */
    MARS = Storage::inst()->AddTexture("textures/mars.tga"),
    JUPITER = Storage::inst()->AddTexture("textures/jupiter.tga"),
    SATURN = Storage::inst()->AddTexture("textures/saturn.tga"),
    URANUS = Storage::inst()->AddTexture("textures/uranus.tga"),
    NEPTUNE = Storage::inst()->AddTexture("textures/neptune.tga"),
    PLUTO = Storage::inst()->AddTexture("textures/pluto.tga"),
    GERMANY = Storage::inst()->AddTexture("textures/germany.tga");
  for(size_t i = SUN; i <= PLUTO; ++i) {
    instance->AddObject(
      Object(
        *Storage::inst()->shapes()[0],
        instance->planet_program, i,
        0.1,
        -0.8 + i/6.0f,
        0.8f - i/6.0f,
        0
      )
    );
  }
}

void Planetarium::Clear() {
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
