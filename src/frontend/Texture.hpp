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
  void AttachToShader(gl::Program &program);
  enum {
    BIND_DEFAULT_OPTIONS=0,
    BIND_INDEX_DEFAULT=0,
    BIND_NO_ACTIVATION=1,
    BIND_NO_SET_DATA=2
  };
  void Bind(size_t index = BIND_INDEX_DEFAULT, int options = BIND_DEFAULT_OPTIONS);
  static void Unbind();
  void Clear();
};
}
