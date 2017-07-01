#pragma once

#include <string>

#include "freetype_config.h"
#include <freetype/ftglyph.h>
#include "incgraphics.h"
#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Image.hpp"
#include "File.hpp"

namespace gl {
struct Texture {
  GLuint tex;
  Uniform<UniformType::SAMPLER2D>u_samp;
  Texture();
  ~Texture();
  img::Image *NewImage(File &file);
  void Init(std::string filename);
  void Init(FT_GlyphSlot *glyph);
  void AttachToShader(ShaderProgram &program);
  void Bind(size_t index = 0);
  static void Unbind();
  void Clear();
};
}
