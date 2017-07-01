#include "ShaderProgram.hpp"
#include "Debug.hpp"

#include <iostream>
#include <vector>


GLuint gl::ShaderProgram::last_used_program = 0;
gl::ShaderProgram::ShaderProgram(std::vector <std::string> &&fnames):
  shaders()
{
  for(size_t i = 0; i < fnames.size(); ++i) {
    shaders.push_back(Shader(fnames[i]));
  }
}

gl::ShaderProgram::~ShaderProgram()
{}

void gl::ShaderProgram::compile_program() {
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


GLuint gl::ShaderProgram::id() const {
  return program;
}

void gl::ShaderProgram::Use() {
  if(last_used_program != id()) {
    glUseProgram(id()); GLERROR
    last_used_program = id();
  }
}

void gl::ShaderProgram::Unuse() {
  glUseProgram(0); GLERROR
  last_used_program = 0;
}

void gl::ShaderProgram::Init(const std::vector <std::string> &&locations) {
  compile();
  bind(locations);
  ASSERT(is_valid());
}

void gl::ShaderProgram::compile() {
  compile_program();
}

void gl::ShaderProgram::bind(const std::vector <std::string> &locations) {
  for(size_t i = 0; i < locations.size(); ++i) {
    glBindAttribLocation(program, i, locations[i].c_str()); GLERROR
  }
}

void gl::ShaderProgram::Clear() {
  glDeleteProgram(program); GLERROR
}
