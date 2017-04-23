#include "ShaderProgram.hpp"
#include "Debug.hpp"

#include <iostream>
#include <vector>


GLuint ShaderProgram::last_used_program = 0;
ShaderProgram::ShaderProgram(std::vector <std::string> &&fnames):
  shaders()
{
  for(size_t i = 0; i < fnames.size(); ++i) {
    shaders.push_back(Shader(fnames[i]));
  }
}

ShaderProgram::~ShaderProgram()
{}

void ShaderProgram::compile_program() {
  for(auto &s : shaders) {
    s.Compile();
  }
  program = glCreateProgram(); GLERROR
  ASSERT(program != 0);
  for(auto &s : shaders) {
    glAttachShader(program, s.id); GLERROR
  }
  glLinkProgram(program); GLERROR

  for(auto &s : shaders) {
    glDeleteShader(s.id); GLERROR
  }
}


GLuint ShaderProgram::id() const {
  return program;
}

void ShaderProgram::Use() {
  if(last_used_program != id()) {
    glUseProgram(id()); GLERROR
    last_used_program = id();
  }
}

void ShaderProgram::Unuse() {
  glUseProgram(0); GLERROR
  last_used_program = 0;
}

void ShaderProgram::Init(const std::vector <std::string> &&locations) {
  compile();
  bind(locations);
  ASSERT(is_valid());
}

void ShaderProgram::compile() {
  compile_program();
}

void ShaderProgram::bind(const std::vector <std::string> &locations) {
  for(size_t i = 0; i < locations.size(); ++i) {
    glBindAttribLocation(program, i, locations[i].c_str()); GLERROR
  }
}

void ShaderProgram::Clear() {
  glDeleteProgram(program); GLERROR
}
