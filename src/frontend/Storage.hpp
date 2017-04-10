#pragma once

#include <vector>
#include "incgraphics.h"
#include "Sprite.hpp"

class Shape;

class Storage {
protected:
  Storage();
  ~Storage();
  static Storage *instance;
public:
  static size_t SPHERE, RING1, RING2, RING3, QUAD;
  static Storage *inst();
  static size_t AddColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.);
  static size_t AddTexture(const char *filename);
  static size_t AddFont(const char *filename);
  template <typename T> static size_t AddShape();
  static void Setup();
  static void Clear();
};
