#include "Sprite.hpp"
#include "Log.hpp"

#include <cstring>
#include <glm/gtc/type_ptr.hpp>

Sprite::colorbuffer::colorbuffer(GLuint vbo, GLfloat *buffer):
  vbo(vbo), buffer(buffer)
{}

Sprite::colorbuffer::~colorbuffer() {
  ASSERT(buffer != NULL);
}

Sprite::Sprite()
{}

Sprite::~Sprite() {
}

Sprite *Sprite::inst() {
  return instance;
}

void Sprite::init_color(colorbuffer &cb) {
  ASSERT(cb.vbo == 0);
  glGenBuffers(1, &cb.vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, cb.vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), cb.buffer, GL_STATIC_DRAW); GLERROR
}


void Sprite::add_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
  GLfloat q[] = {
    r,g,b,a,
    r,g,b,a,
    r,g,b,a,
  };
  GLfloat *buf = new GLfloat[12];
  memcpy(buf, q, 12 * sizeof(GLfloat));
  colors_.push_back(colorbuffer(0, buf));
  init_color(colors_.back());
}

void Sprite::add_color(const glm::vec4 &color) {
  GLfloat *b = new GLfloat[12];
  memcpy(b, glm::value_ptr(color), 12 * sizeof(GLfloat));
  colors_.push_back(colorbuffer(0, b));
  init_color(colors_.back());
}

const std::vector <Sprite::colorbuffer> &Sprite::colors() {
  return colors_;
}

Sprite *Sprite::instance = NULL;
void Sprite::Setup() {
  ASSERT(instance == NULL);
  instance = new Sprite();
  instance->add_color(1., 1., 1.);
  instance->add_color(0., 0., 0.);
  instance->add_color(1., 0., 0.);
  instance->add_color(0., 1., 0.);
  instance->add_color(0., 0., 1.);
}

void Sprite::Clear() {
  for(auto &cb : inst()->colors_) {
    ASSERT(cb.vbo != 0);
    glDeleteBuffers(1, &cb.vbo); GLERROR
    /* delete cb.buffer; */
  }
}
