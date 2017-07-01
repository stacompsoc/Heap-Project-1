#pragma once

#include "Image.hpp"

namespace img {
struct BMPImage : public Image {
  BMPImage(const char *filename);
  ~BMPImage();
  void Load();
};
}
