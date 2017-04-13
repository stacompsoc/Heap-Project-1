#include "PNGImage.hpp"
#include "Log.hpp"

#include <cstdio>
#include <setjmp.h>
#include <png.h>

PNGImage::PNGImage(const char *filename):
  Image(filename)
{}

PNGImage::~PNGImage()
{}

void PNGImage::Load() {
  unsigned char header[8];    // 8 is the maximum size that can be checked

  /* open file and test for it being a png */
  FILE *fp = fopen(filename.c_str(), "rb");
  ASSERT(fp != NULL);
  fread(header, 1, 8, fp);
  if(png_sig_cmp(header, 0, 8)) {
    gl_log("[read_png_file] File %s is not recognized as a PNG file", filename.c_str());
    return;
  }


  /* initialize stuff */
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(png_ptr == NULL) {
    gl_log("[read_png_file] png_create_read_struct failed");
    return;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr) {
    gl_log("[read_png_file] png_create_info_struct failed");
    return;
  }

  if(setjmp(png_jmpbuf(png_ptr))) {
    gl_log("[read_png_file] Error during init_io");
    return;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  int color_type = png_get_color_type(png_ptr, info_ptr);
  int bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  int number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);


  /* read file */
  if(setjmp(png_jmpbuf(png_ptr))) {
    gl_log("[read_png_file] Error during read_image");
    return;
  }

  png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
  for (size_t y = 0; y < height; ++y)
    row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr,info_ptr));

  png_read_image(png_ptr, row_pointers);

  fclose(fp);

  if(png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB) {
    gl_log("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
           "(lacks the alpha channel)");
    return;
  }

  if(png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA) {
    gl_log("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
           PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));
    return;
  }

  size_t bpp = 4;
  data = new unsigned char[height * width * bpp];
  for (size_t y = 0; y < height; ++y) {
    png_byte *row = row_pointers[y];
    for (size_t x = 0; x < width; ++x) {
      png_byte *ptr = &(row[x*4]);
      /* printf("Pixel at position [ %lu - %lu ] has RGBA values: %d - %d - %d - %d\n", */
      /*        x, y, ptr[0], ptr[1], ptr[2], ptr[3]); */
      /* set red value to 0 and green value to the blue one */
      unsigned char *dataptr = &data[bpp * ((height - 1 - y) * width + x)];
      dataptr[0] = ptr[0];
      dataptr[1] = ptr[1];
      dataptr[2] = ptr[2];
      dataptr[3] = ptr[3];
    }
  }

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  for(size_t y = 0; y < height; ++y)
    free(row_pointers[y]);
  free(row_pointers);
}
