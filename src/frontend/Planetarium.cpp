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
  Cam()->UniformUpdate();
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
    MOON = Storage::inst()->AddTexture("textures/moon.tga"),
    MARS = Storage::inst()->AddTexture("textures/mars.tga"),
    JUPITER = Storage::inst()->AddTexture("textures/jupiter.tga"),
    SATURN = Storage::inst()->AddTexture("textures/saturn.tga"),
    URANUS = Storage::inst()->AddTexture("textures/uranus.tga"),
    NEPTUNE = Storage::inst()->AddTexture("textures/neptune.tga"),
    PLUTO = Storage::inst()->AddTexture("textures/pluto.tga");
  float posx = -.95, posy = .95;
  for(size_t i = SUN; i <= PLUTO; ++i) {
    double r = .1;
    posx += r + .05;
    posy -= r + .05;
    instance->AddObject(
      Object(
        *Storage::inst()->shapes()[0],
        instance->planet_program, i,
        r, posx,posy,0,
        .0001
      )
    );
  }
  /* instance->AddObject( */
  /*   Object( */
  /*     *Storage::inst()->shapes()[0], */
  /*     instance->planet_program, EARTH, */
  /*     0.5f, 0,0,0, */
  /*     24 */
  /*   ) */
  /* ); */
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
