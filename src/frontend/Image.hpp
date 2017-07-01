#pragma once

#include <string>
#include "incgraphics.h"

namespace img {
struct Image {
  size_t width, height, depth = 1;
  GLenum format = GL_RGBA;
  unsigned char *data = NULL;
  std::string filename;
  Image(const char *filename);
  virtual ~Image();
  virtual void Load() = 0;
  virtual void Clear();
};
}
