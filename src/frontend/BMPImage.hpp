#pragma once

#include "Image.hpp"

struct BMPImage : public Image {
  BMPImage(const char *filename);
  ~BMPImage();
  void Load();
};
