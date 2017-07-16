#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "Shader.hpp"
#include "incgraphics.h"

namespace gl {
class Program {
  static GLuint last_used_program;
  GLuint program = 0;
  std::vector<Shader> shaders;
  void compile_program();
  void bind(const std::vector <std::string> &locations);
  bool is_valid();
  void print_info_log();
  void print_all();
public:
  Program(std::vector <std::string> &&fnames);
  ~Program();
  GLuint id() const;
  void Init(const std::vector <std::string> &&locations);
  void Compute(size_t x, size_t y, size_t z);
  void Use();
  static void Unuse();
  void Clear();
};
}
