#include "Font.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

Font::Font()
{}

Font::~Font()
{}

void Font::Init(const char *filename) {
  ASSERT(initialized);
  int rc = FT_New_Face(ft, filename, 0, &face);
  ASSERT(!rc);
  FT_Set_Pixel_Sizes(face, 0, 48);

  for(GLubyte c = 0; c < 128; ++c) {
    int rc = FT_Load_Char(face, c, FT_LOAD_RENDER);
    ASSERT(!rc);
    Character chrtex = {
      Texture(),
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      GLuint(face->glyph->advance.x)
    };
    chrtex.tex.Init(&face->glyph);
    alphabet[c] = chrtex;
  }
  Logger::Info("Initialized font from file %s\n", filename);
}

void Font::Clear() {
  FT_Done_Face(face);
  for(auto &it : alphabet)
    it.second.tex.Clear();
}

FT_Library Font::ft;
bool Font::initialized = false;
void Font::Setup() {
  ASSERT(!initialized);
  int rc = FT_Init_FreeType(&ft);
  ASSERT(!rc);
  initialized = true;
}

void Font::Cleanup() {
  ASSERT(initialized);
  FT_Done_FreeType(ft);
  initialized = false;
}
