#pragma once

#include "Image.hpp"

struct PNGImage : public Image {
  PNGImage(const char *filename);
  ~PNGImage();
  void Load();
};
