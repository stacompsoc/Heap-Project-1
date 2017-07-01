#pragma once

#include <map>
#include <glm/glm.hpp>
#include "freetype_config.h"
#include "Texture.hpp"

struct Font {
  static bool initialized;
  static FT_Library ft;
  FT_Face face;
  struct Character {
    gl::Texture tex;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
  };
  std::map <GLchar, Character> alphabet;
  Font();
  ~Font();
  void Init(const char *filename);
  void Clear();
  static void Setup();
  static void Cleanup();
};
