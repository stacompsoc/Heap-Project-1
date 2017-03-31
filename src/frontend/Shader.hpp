#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "incgraphics.h"

class ShaderProgram {
  struct Shader {
    std::string filename;
    GLenum type = 0;
    GLuint id = 0;

    Shader(std::string &filename);
    ~Shader();
    bool is_ext(const std::string &&ext);
    size_t file_length();
    char *load_text_file();
    void Compile();
  };
  GLuint
    program = 0;
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
  void Init(const std::vector <std::string> &&locations);
  void Clear();
};
