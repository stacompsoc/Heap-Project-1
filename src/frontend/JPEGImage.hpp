#pragma once

#include "Image.hpp"

namespace img {
struct JPEGImage : public Image {
  JPEGImage(const char *filename);
  ~JPEGImage();
  void Load();
};
}
