#pragma once

#include "Image.hpp"

namespace img {
struct PNGImage : public Image {
  PNGImage(const char *filename);
  ~PNGImage();
  void Load();
};
}
