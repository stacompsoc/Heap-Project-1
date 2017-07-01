#include "Image.hpp"

img::Image::Image(const char *filename):
  filename(filename)
{}

img::Image::~Image()
{}

void img::Image::Clear() {
  width=0,height=0,depth=1;
  delete [] data;
  data = NULL;
}
