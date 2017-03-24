#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "incgraphics.h"

class Sprite {
public:
  struct colorbuffer {
    GLuint vbo;
    GLfloat *buffer;
    colorbuffer(GLuint, GLfloat *);
    ~colorbuffer();
  };
protected:
  std::vector <colorbuffer> colors_;
  void init_color(colorbuffer &cb);
  Sprite();
  ~Sprite();
  static Sprite *instance;
public:
  static Sprite *inst();
  void add_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.);
  void add_color(const glm::vec4 &color);
  const std::vector <colorbuffer> &colors();
  static void setup();
};
