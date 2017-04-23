#pragma once

#include <string>

class File {
  std::string filename;
public:
  File(const char *filename);
  ~File();
  size_t length();
  const std::string &name() const;
  std::string name();
  bool is_ext(const std::string &&ext);
  bool exists();
  char *load_text();
};
