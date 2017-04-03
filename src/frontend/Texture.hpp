#pragma once

#include <string>

#include "freetype_config.h"
#include <freetype/ftglyph.h>
#include "incgraphics.h"
#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"

struct Texture {
  GLuint tex;
  Uniform<SAMPLER2D>u_samp;
  unsigned char *data = NULL;
  size_t width = 0, height = 0;
  Texture();
  ~Texture();
  void LoadTGA(const char *filename);
  void LoadDummy();
  void Init(std::string filename);
  void Init(FT_GlyphSlot *glyph);
  void AttachToShader(ShaderProgram &program);
  void Bind(size_t index = 0);
  static void Unbind();
  void Clear();
};
