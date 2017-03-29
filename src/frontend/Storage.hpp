#pragma once

#include <type_traits>
#include <vector>
#include <glm/glm.hpp>
#include "incgraphics.h"
#include "Texture.hpp"

class Shape;

class Storage {
public:
  struct colorbuffer {
    GLuint vbo = 0;
    colorbuffer();
    ~colorbuffer();
  };
protected:
  std::vector <colorbuffer> colors_;
  std::vector <Texture> textures_;
  std::vector <Shape *> shapes_;
  void init_color(colorbuffer &cb, const GLfloat *buffer);
  Storage();
  ~Storage();
  static Storage *instance;
public:
  static Storage *inst();
  size_t AddColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.);
  size_t AddColor(const glm::vec4 &color);
  size_t AddTexture(const char *filename);
  template <typename T>
  size_t AddShape();
  const std::vector <colorbuffer> &colors();
  std::vector <Texture> &textures();
  const std::vector <Shape *> &shapes();
  static void Setup();
  static void Clear();
};