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
  gl::ColorBuffer cb;
  cb.Init(q);
  return Sprite<gl::ColorBuffer>::Add(cb);
}

size_t Storage::AddTexture(const char *filename) {
  gl::Texture texture;
  texture.Init(filename);
  return Sprite<gl::Texture>::Add(texture);
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
  long c = clock();
  ASSERT(instance == NULL);
  Font::Setup();
  std::cout << "font init: " << clock()-c << std::endl;
  c=clock();
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
  std::cout << "sphere init: " << clock()-c << std::endl;
  c=clock();
  RING1 = instance->AddShape<Ring <1> >();
  std::cout << "ring1 init: " << clock()-c << std::endl;
  c=clock();
  RING2 = instance->AddShape<Ring <2> >();
  std::cout << "ring2 init: " << clock()-c << std::endl;
  c=clock();
  RING3 = instance->AddShape<Ring <3> >();
  std::cout << "ring3 init: " << clock()-c << std::endl;
  c=clock();
  /* RING7 = instance->AddShape<Ring <7> >(); */
  /* RING8 = instance->AddShape<Ring <8> >(); */
  QUAD = instance->AddShape<Quad>();
  std::cout << "quad init: " << clock()-c << std::endl;
  c=clock();
}

void Storage::Clear() {
  ASSERT(instance != NULL);
  Sprite<gl::ColorBuffer>::Cleanup();
  Sprite<gl::Texture>::Cleanup();
  Sprite<Font>::Cleanup();
  Sprite<Shape *>::Cleanup();
  Font::Cleanup();
  delete instance;
  instance = NULL;
}
