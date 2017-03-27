#pragma once

#include <string>

#include "incgraphics.h"
#include "Shader.hpp"

struct Texture {
  static int g_texcounter;
  int texcounter;
  GLuint tex;
  unsigned char *data = NULL;
  size_t width = 0, height = 0;
  Texture();
  ~Texture();
  void LoadTGA(const char *filename);
  void Init(std::string filename);
  void AttachToShader(ShaderProgram &program) const;
  void Bind() const;
  void Unbind() const;
  void Clear();
};
