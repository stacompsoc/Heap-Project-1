#pragma once

#include <string>

#include "incgraphics.h"
#include "Shader.hpp"

struct Texture {
  static int g_texcounter;
  int texcounter;
  GLuint tex;
  GLuint u_samp;
  unsigned char *data = NULL;
  size_t width = 0, height = 0;
  Texture();
  ~Texture();
  void LoadTGA(const char *filename);
  void Init(std::string filename);
  void AttachToShader(ShaderProgram &program);
  void Bind() const;
  void Unbind() const;
  void Clear();
};
