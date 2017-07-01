#include "Texture.hpp"
#include "Debug.hpp"
#include "Logger.hpp"
#include "Font.hpp"

#include "PNGImage.hpp"
#include "JPEGImage.hpp"
#include "TIFFImage.hpp"
#include "BMPImage.hpp"

#include <fstream>

gl::Texture::Texture():
  u_samp("samp")
{}

gl::Texture::~Texture()
{}

img::Image *gl::Texture::NewImage(File &file) {
  ASSERT(file.exists());
  if(file.is_ext(".png")) {
    return new img::PNGImage(file.name().c_str());
  } else if(file.is_ext(".jpg") || file.is_ext(".jpeg")) {
    return new img::JPEGImage(file.name().c_str());
  } else if(file.is_ext(".tiff")) {
    return new img::TIFFImage(file.name().c_str());
  } else if(file.is_ext(".bmp")) {
    return new img::BMPImage(file.name().c_str());
  }
  Logger::Error("unsupported file format for %s\n", file.name().c_str());
  throw std::domain_error("invalid image format for " + file.name());
}

void gl::Texture::Init(std::string filename) {
  Logger::Info("Loading texture '%s'\n", filename.c_str());
  File file(filename.c_str());
  img::Image *image = NewImage(file);
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
  Logger::Info("Finished loading texture '%s'.\n", filename.c_str());
}

void gl::Texture::Init(FT_GlyphSlot *glyph) {
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

void gl::Texture::AttachToShader(ShaderProgram &program) {
  ASSERT(program.id() != 0);
  u_samp.set_id(program.id());
}

void gl::Texture::Bind(size_t index) {
  glActiveTexture(GL_TEXTURE0 + index); GLERROR
  glBindTexture(GL_TEXTURE_2D, tex); GLERROR
  u_samp.set_data(index);
}

void gl::Texture::Unbind() {
  glBindTexture(GL_TEXTURE_2D, 0); GLERROR
}

void gl::Texture::Clear() {
  glDeleteTextures(1, &tex);
}
