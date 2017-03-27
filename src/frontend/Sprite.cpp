#include "Sprite.hpp"
#include "Log.hpp"

#include <cstring>
#include <glm/gtc/type_ptr.hpp>

Sprite::colorbuffer::colorbuffer()
{}

Sprite::colorbuffer::~colorbuffer()
{}

Sprite::Sprite()
{}

Sprite::~Sprite()
{}

Sprite *Sprite::inst() {
  return instance;
}

void Sprite::init_color(colorbuffer &cb, const GLfloat *buffer) {
  glGenBuffers(1, &cb.vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, cb.vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), buffer, GL_STATIC_DRAW); GLERROR
}


void Sprite::AddColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
  GLfloat q[] = {
    r,g,b,a,
    r,g,b,a,
    r,g,b,a,
  };
  colors_.push_back(colorbuffer());
  init_color(colors_.back(), q);
}

void Sprite::AddColor(const glm::vec4 &color) {
  colors_.push_back(colorbuffer());
  init_color(colors_.back(), glm::value_ptr(color));
}

void Sprite::AddTexture(const char *filename) {
  textures_.push_back(Texture());
  textures_.back().Init(filename);
}

const std::vector <Sprite::colorbuffer> &Sprite::colors() {
  return colors_;
}

const std::vector <Texture> &Sprite::textures() {
  return textures_;
}

Sprite *Sprite::instance = NULL;
void Sprite::Setup() {
  ASSERT(instance == NULL);
  instance = new Sprite();
  instance->AddColor(1., 1., 1.);
  instance->AddColor(0., 0., 0.);
  instance->AddColor(1., 0., 0.);
  instance->AddColor(0., 1., 0.);
  instance->AddColor(0., 0., 1.);
  instance->AddColor(0., 1., 1.);
  instance->AddColor(1., 0., 1.);
  instance->AddColor(1., 1., 0.);
}

void Sprite::Clear() {
  ASSERT(instance != NULL);
  for(auto &cb : instance->colors_) {
    glDeleteBuffers(1, &cb.vbo); GLERROR
  }
  for(auto &tex : instance->textures_) {
    tex.Clear();
  }
  delete instance;
  instance = NULL;
}
