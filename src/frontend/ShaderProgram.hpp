#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "Shader.hpp"
#include "incgraphics.h"

class ShaderProgram {
  static GLuint last_used_program;
  GLuint program = 0;
  std::vector <Shader> shaders;
  void compile_program();
  void compile();
  void bind(const std::vector <std::string> &locations);
  bool is_valid();
  void print_info_log();
  void print_all();
public:
  ShaderProgram(std::vector <std::string> &&fnames);
  ~ShaderProgram();
  GLuint id() const;
  void Use();
  static void Unuse();
  void Init(const std::vector <std::string> &&locations);
  void Clear();
};
