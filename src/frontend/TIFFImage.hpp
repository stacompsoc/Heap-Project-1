#pragma once

#include "Image.hpp"

namespace img {
struct TIFFImage : public Image {
  TIFFImage(const char *filename);
  ~TIFFImage();
  void Load();
};
}
