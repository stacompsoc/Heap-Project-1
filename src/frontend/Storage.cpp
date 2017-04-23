#include "Storage.hpp"
#include "Debug.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Ring.hpp"
#include "Quad.hpp"
#include "ColorBuffer.hpp"
#include "Font.hpp"
#include "Texture.hpp"

#include <type_traits>

Storage::Storage()
{}

Storage::~Storage()
{}

Storage *Storage::inst() {
  return instance;
}

size_t Storage::AddColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
  GLfloat q[] = {
    r,g,b,a,
    r,g,b,a,
    r,g,b,a,
  };
  ColorBuffer cb;
  cb.Init(q);
  return Sprite<ColorBuffer>::Add(cb);
}

size_t Storage::AddTexture(const char *filename) {
  Texture texture;
  texture.Init(filename);
  return Sprite<Texture>::Add(texture);
}

size_t Storage::AddFont(const char *filename) {
  Font font;
  font.Init(filename);
  return Sprite<Font>::Add(font);
}

template <typename T>
size_t Storage::AddShape() {
  using S = typename std::enable_if<std::is_base_of<Shape, T>::value, T>::type;
  Shape *sh = new S();
  sh->Init();
  return Sprite<Shape *>::Add(sh);
}

size_t Storage::SPHERE = 0;
size_t Storage::RING1 = 0;
size_t Storage::RING2 = 0;
size_t Storage::RING3 = 0;
size_t Storage::RING7 = 0;
size_t Storage::RING8 = 0;
size_t Storage::QUAD = 0;
Storage *Storage::instance = NULL;
void Storage::Setup() {
  ASSERT(instance == NULL);
  Font::Setup();
  instance = new Storage();
  AddColor(1., 1., 1.);
  AddColor(0., 0., 0.);
  AddColor(1., 0., 0.);
  AddColor(0., 1., 0.);
  AddColor(0., 0., 1.);
  AddColor(0., 1., 1.);
  AddColor(1., 0., 1.);
  AddColor(1., 1., 0.);
  SPHERE = instance->AddShape<Sphere>();
  RING1 = instance->AddShape<Ring <1> >();
  RING2 = instance->AddShape<Ring <2> >();
  RING3 = instance->AddShape<Ring <3> >();
  RING7 = instance->AddShape<Ring <7> >();
  RING8 = instance->AddShape<Ring <8> >();
  QUAD = instance->AddShape<Quad>();
}

void Storage::Clear() {
  ASSERT(instance != NULL);
  Sprite<ColorBuffer>::Cleanup();
  Sprite<Texture>::Cleanup();
  Sprite<Font>::Cleanup();
  Sprite<Shape *>::Cleanup();
  Font::Cleanup();
  delete instance;
  instance = NULL;
}
