#include "Texture.hpp"
#include "Log.hpp"
#include "Font.hpp"

#include "PNGImage.hpp"
#include "JPEGImage.hpp"
#include "TIFFImage.hpp"
#include "BMPImage.hpp"

#include <fstream>

Texture::Texture():
  u_samp("samp")
{}

Texture::~Texture()
{}

Image *Texture::NewImage(File &file) {
  ASSERT(file.exists());
  if(file.is_ext(".png")) {
    return new PNGImage(file.name().c_str());
  } else if(file.is_ext(".jpg") || file.is_ext(".jpeg")) {
    return new JPEGImage(file.name().c_str());
  } else if(file.is_ext(".tiff")) {
    return new TIFFImage(file.name().c_str());
  } else if(file.is_ext(".bmp")) {
    return new BMPImage(file.name().c_str());
  }
  throw std::runtime_error("invalid image format");
}

void Texture::Init(std::string filename) {
  gl_log("Loading texture '%s'\n", filename.c_str());
  File file(filename.c_str());
  Image *image = NewImage(file);
  image->Load();
  glGenTextures(1, &tex); GLERROR
  glBindTexture(GL_TEXTURE_2D, tex); GLERROR
  glTexImage2D(GL_TEXTURE_2D, 0, image->format, image->width, image->height, 0, image->format, GL_UNSIGNED_BYTE, image->data); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); GLERROR
  glGenerateMipmap(GL_TEXTURE_2D); GLERROR
  Unbind();
  image->Clear();
  delete image;
  gl_log("Finished loading texture '%s'.\n", filename.c_str());
}

void Texture::Init(FT_GlyphSlot *glyph) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); GLERROR
  glGenTextures(1, &tex); GLERROR
  glBindTexture(GL_TEXTURE_2D, tex); GLERROR
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (*glyph)->bitmap.width, (*glyph)->bitmap.rows,
               0, GL_RED, GL_UNSIGNED_BYTE, (*glyph)->bitmap.buffer); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); GLERROR
  Unbind();
}

void Texture::AttachToShader(ShaderProgram &program) {
  ASSERT(program.id() != 0);
  u_samp.set_id(program.id());
}

void Texture::Bind(size_t index) {
  glActiveTexture(GL_TEXTURE0 + index); GLERROR
  glBindTexture(GL_TEXTURE_2D, tex); GLERROR
  u_samp.set_data(index);
}

void Texture::Unbind() {
  glBindTexture(GL_TEXTURE_2D, 0); GLERROR
}

void Texture::Clear() {
  glDeleteTextures(1, &tex);
}
