#pragma once

#include <string>

struct Image {
  size_t width, height, depth = 1;
  unsigned char *data = NULL;
  std::string filename;
  Image(const char *filename);
  ~Image();
  virtual void Load() = 0;
  virtual void Clear();
};
