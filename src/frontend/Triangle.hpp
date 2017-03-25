#pragma once

#include "Sprite.hpp"
#include "incgraphics.h"

struct Triangle {
  struct vertexbuffer {
    GLuint vbo = 0;
    GLfloat *buffer;
    vertexbuffer(GLfloat *buffer);
    ~vertexbuffer();
  };
  GLuint vao = 0;
  vertexbuffer vb;
  GLuint cb_vbo;
  Triangle();
  ~Triangle();
  void Init(GLfloat *positions, size_t color_id);
  void init_vertices();
  void init_array_object();
  void disable_vao_attribs();
  void ChangePosition();
  void ChangeColor(size_t color_id);
  void Draw() const;
  void Clear();
};
