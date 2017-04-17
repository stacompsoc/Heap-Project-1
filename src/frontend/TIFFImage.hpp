#pragma once

#include "Image.hpp"

struct TIFFImage : public Image {
  TIFFImage(const char *filename);
  ~TIFFImage();
  void Load();
};
