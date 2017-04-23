#include "Image.hpp"

Image::Image(const char *filename):
  filename(filename)
{}

Image::~Image()
{}

void Image::Clear() {
  width=0,height=0,depth=1;
  delete [] data;
  data = NULL;
}
