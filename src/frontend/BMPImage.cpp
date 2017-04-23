#include "BMPImage.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

#include <omp.h>

BMPImage::BMPImage(const char *filename):
  Image(filename)
{}

BMPImage::~BMPImage()
{}

void BMPImage::Load() {
  unsigned char header[138];
  size_t data_pos, img_size;

  // Open the file
  FILE *file = fopen(filename.c_str(),"rb");
  ASSERT(file != NULL);

  // If less than 54 bytes are read, problem
  size_t r;
  if((r = fread(header, sizeof(unsigned char), 138, file)) != 138)
    throw std::runtime_error("error reading header of file " + filename + ", length " + std::to_string(r));

  // file signature
  ASSERT(header[0] == 'B' && header[1] == 'M');

  // make sure this is a 24bpp file
  ASSERT(*(int32_t*)&(header[0x1E]) == 0);
  ASSERT(*(int32_t*)&(header[0x1C]) == 24);

  data_pos = *(int32_t*)&(header[0x0A]);
  img_size = *(int32_t*)&(header[0x22]);
  width = *(int32_t*)&(header[0x12]);
  height = *(int32_t*)&(header[0x16]);

  size_t bpp = 3;
  format = GL_RGB;
  // Some BMP files are misformatted, guess missing information
  if(img_size == 0 || img_size != width * height * bpp) {
    Logger::Warning("[bmp] warning: file [%s] has incorrect img_size %d\n", filename.c_str(), img_size);
    img_size = width * height * bpp;
  }
  if(data_pos != 138) {
    Logger::Warning("[bmp] warning: file [%s] has incorrect data_pos %d\n", filename.c_str(), data_pos);
    data_pos = 138;
  }
  ASSERT(img_size == width * height * bpp);

  data = new unsigned char[img_size];
  unsigned char *row = new unsigned char[width * bpp];
  for(size_t y = 0; y < height; ++y) {
    r = fread(row, sizeof(unsigned char), width*bpp, file);
    ASSERT(r == width  * bpp);
    #pragma omp parallel for num_threads(4)
    for(size_t x = 0; x < width; ++x) {
      unsigned char
        *dptr = &data[width * y * bpp + x * bpp],
        *rptr = &row[x * bpp];
      dptr[0] = rptr[2];
      dptr[1] = rptr[1];
      dptr[2] = rptr[0];
    }
  }
  delete [] row;
  fclose(file);
}
