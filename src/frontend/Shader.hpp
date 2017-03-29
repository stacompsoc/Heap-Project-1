#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "incgraphics.h"

class ShaderProgram {
  GLuint
    program = 0;
  GLuint
    vert = 0,
    geom = 0,
    frag = 0;
  const std::string
    vert_fname,
    geom_fname,
    frag_fname;

  static char *load_text_file(const char *filename);
  void compile_shader(GLuint &shader, GLenum type, const char *filename);
  void compile_program();

  void compile();
  void bind(const std::vector <std::string> &locations);
  bool is_valid();
  void print_info_log();
  void print_all();
public:
  ShaderProgram(const char *vert, const char *geom, const char *frag);
  ~ShaderProgram();
  GLuint id() const;
  void Use();
  void Init(const std::vector <std::string> &&locations);
  void Clear();
};
