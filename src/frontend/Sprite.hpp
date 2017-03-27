#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "incgraphics.h"
#include "Texture.hpp"

class Sprite {
public:
  struct colorbuffer {
    GLuint vbo = 0;
    colorbuffer();
    ~colorbuffer();
  };
protected:
  std::vector <colorbuffer> colors_;
  std::vector <Texture> textures_;
  void init_color(colorbuffer &cb, const GLfloat *buffer);
  Sprite();
  ~Sprite();
  static Sprite *instance;
public:
  static Sprite *inst();
  void AddColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.);
  void AddColor(const glm::vec4 &color);
  void AddTexture(const char *filename);
  const std::vector <colorbuffer> &colors();
  const std::vector <Texture> &textures();
  static void Setup();
  static void Clear();
};
