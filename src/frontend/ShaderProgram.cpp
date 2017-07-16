#include "ShaderProgram.hpp"
#include "Debug.hpp"

#include <iostream>
#include <vector>


GLuint gl::Program::last_used_program = 0;
gl::Program::Program(std::vector <std::string> &&fnames):
  shaders()
{
  for(size_t i = 0; i < fnames.size(); ++i) {
    shaders.push_back(Shader(fnames[i]));
  }
}

gl::Program::~Program()
{}

void gl::Program::compile_program() {
  for(auto &s : shaders) {
    s.Compile();
  }
  program = glCreateProgram(); GLERROR
  ASSERT(program != 0);
  for(auto &s : shaders) {
    glAttachShader(program, s.id); GLERROR
  }
  glLinkProgram(program); GLERROR

  for(auto &s : shaders)
    s.Clear();
}

void gl::Program::bind(const std::vector <std::string> &locations) {
  for(size_t i = 0; i < locations.size(); ++i) {
    glBindAttribLocation(program, i, locations[i].c_str()); GLERROR
  }
}


GLuint gl::Program::id() const {
  return program;
}

void gl::Program::Init(const std::vector <std::string> &&locations) {
  compile_program();
  bind(locations);
  ASSERT(is_valid());
}

void gl::Program::Compute(size_t x, size_t y, size_t z) {
  for(auto &s : shaders) {
    if(s.type == GL_COMPUTE_SHADER) {
      s.Dispatch(x, y, z);
    }
  }
}

void gl::Program::Use() {
  if(last_used_program != id()) {
    glUseProgram(id()); GLERROR
    last_used_program = id();
  }
}

void gl::Program::Unuse() {
  glUseProgram(0); GLERROR
  last_used_program = 0;
}

void gl::Program::Clear() {
  for(auto &s : shaders)
    glDetachShader(program, s.id); GLERROR
  glDeleteProgram(program); GLERROR
}
