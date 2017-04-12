#pragma once

#include "incgraphics.h"
#include "Storage.hpp"
#include "VertexArray.hpp"

struct Triangle {
  struct vertexbuffer {
    GLuint vbo = 0;
    vertexbuffer();
    ~vertexbuffer();
  };
  struct texcoordbuffer {
    bool is_enabled = false;
    GLuint vbo = 0;
    texcoordbuffer();
    ~texcoordbuffer();
  };
  VertexArray vao;
  vertexbuffer vb;
  texcoordbuffer tex;
  GLuint cb_vbo;
  Triangle();
  ~Triangle();
  void Init(GLfloat *positions, size_t color_id);
  void Init(GLfloat *positions, GLfloat *texpositions);
  void init_vertices(GLfloat *buffer);
  void init_texcoords(GLfloat *buffer);
  void init_array_object();
  void disable_vao_attribs();
  void ChangePosition();
  void ChangeColor(size_t color_id);
  void Draw();
  void Clear();
};
