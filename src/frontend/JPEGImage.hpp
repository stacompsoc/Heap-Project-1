#pragma once

#include "Image.hpp"

struct JPEGImage : public Image {
  JPEGImage(const char *filename);
  ~JPEGImage();
  void Load();
};
