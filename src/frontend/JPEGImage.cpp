#include "JPEGImage.hpp"
#include "Log.hpp"

#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>

JPEGImage::JPEGImage(const char *filename):
  Image(filename)
{}

JPEGImage::~JPEGImage()
{}

// TODO: need alpha chanel byte per pixel
void JPEGImage::Load() {
  unsigned char *rowptr[1];    // pointer to an array
  struct jpeg_decompress_struct info; //for our jpeg info
  struct jpeg_error_mgr err;          //the error handler

  FILE* file = fopen(filename.c_str(), "rb");  //open the file
  ASSERT(file != NULL);

  info.err = jpeg_std_error(& err);
  jpeg_create_decompress(& info);   //fills info structure

  jpeg_stdio_src(&info, file);
  jpeg_read_header(&info, TRUE);   // read jpeg file header

  jpeg_start_decompress(&info);    // decompress the file

  //set width and height
  size_t bpp = info.num_components;
  width = info.output_width;
  height = info.output_height;
  if(bpp == 3)
    format = GL_RGB;
  else if(bpp == 4)
    format = GL_RGBA;
  else
    throw std::runtime_error("error: unknown pixel format");

  data = new unsigned char[width * height * bpp];
  while(info.output_scanline < info.output_height) {
    // Enable jpeg_read_scanlines() to fill our jdata array
    rowptr[0] = (unsigned char *)data + /* secret to method */ bpp * width * (height - 1 - info.output_scanline);
    jpeg_read_scanlines(&info, rowptr, 1);
  }
  jpeg_finish_decompress(&info);
  jpeg_destroy_decompress(&info);
  fclose(file);
}
