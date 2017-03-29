#include "Storage.hpp"
#include "Log.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"

#include <cstring>
#include <glm/gtc/type_ptr.hpp>

Storage::colorbuffer::colorbuffer()
{}

Storage::colorbuffer::~colorbuffer()
{}

Storage::Storage()
{}

Storage::~Storage()
{}

Storage *Storage::inst() {
  return instance;
}

void Storage::init_color(colorbuffer &cb, const GLfloat *buffer) {
  glGenBuffers(1, &cb.vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, cb.vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), buffer, GL_STATIC_DRAW); GLERROR
}


size_t Storage::AddColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
  GLfloat q[] = {
    r,g,b,a,
    r,g,b,a,
    r,g,b,a,
  };
  colors_.push_back(colorbuffer());
  init_color(colors_.back(), q);
  return colors().size() - 1;
}

size_t Storage::AddColor(const glm::vec4 &color) {
  colors_.push_back(colorbuffer());
  init_color(colors_.back(), glm::value_ptr(color));
  return colors().size() - 1;
}

size_t Storage::AddTexture(const char *filename) {
  textures_.push_back(Texture());
  textures_.back().Init(filename);
  return textures().size() - 1;
}

template <typename T>
size_t Storage::AddShape() {
  using S = typename std::enable_if<std::is_base_of<Shape, T>::value, T>::type;
  shapes_.push_back(new S());
  shapes_.back()->Init();
  return shapes().size() - 1;
}

const std::vector <Storage::colorbuffer> &Storage::colors() {
  ASSERT(instance != NULL);
  return colors_;
}

std::vector <Texture> &Storage::textures() {
  ASSERT(instance != NULL);
  return textures_;
}

const std::vector <Shape *> &Storage::shapes() {
  ASSERT(instance != NULL);
  return shapes_;
}

Storage *Storage::instance = NULL;
void Storage::Setup() {
  ASSERT(instance == NULL);
  instance = new Storage();
  instance->AddColor(1., 1., 1.);
  instance->AddColor(0., 0., 0.);
  instance->AddColor(1., 0., 0.);
  instance->AddColor(0., 1., 0.);
  instance->AddColor(0., 0., 1.);
  instance->AddColor(0., 1., 1.);
  instance->AddColor(1., 0., 1.);
  instance->AddColor(1., 1., 0.);
  instance->AddTexture("triangle.tga");
  instance->AddShape<Sphere>();
}

void Storage::Clear() {
  ASSERT(instance != NULL);
  for(auto &cb : instance->colors_) {
    glDeleteBuffers(1, &cb.vbo); GLERROR
  }
  for(auto &tex : instance->textures_) {
    tex.Clear();
  }
  for(auto &sh : instance->shapes_) {
    sh->Clear();
    delete sh;
  }
  delete instance;
  instance = NULL;
}
