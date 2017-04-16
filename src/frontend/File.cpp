#include "File.hpp"

#include <cassert>
#include <sys/stat.h>

File::File(const char *filename):
  filename(filename)
{}

File::~File()
{}

size_t File::length() {
  struct stat st;
  stat(filename.c_str(), &st);
  return st.st_size;
}

const std::string &File::name() const {
  return filename;
}

std::string File::name() {
  return filename;
}

bool File::is_ext(const std::string &&ext) {
  if(ext.length() > filename.length())
    return false;
  size_t f=filename.length(),e=ext.length();
  return filename.substr(f-e, e) == ext;
}

unsigned char *File::load() {
  size_t size = length() + 1;
  char *text = (char *)malloc(size * sizeof(char));
  assert(text != NULL);

  FILE *file = fopen(filename.c_str(), "r");
  assert(file != NULL);

  char *t = text;
  while((*t = fgetc(file)) != EOF)
    ++t;
  *t = '\0';

  fclose(file);
  return (unsigned char *)text;
}
