#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <sys/stat.h>

#include "Shader.hpp"
#include "Log.hpp"

ShaderProgram::Shader::Shader(std::string &filename):
  filename(filename)
{
  if(is_ext(".vert")) {
    type = GL_VERTEX_SHADER;
  } else if(is_ext(".tesc")) {
    type = GL_TESS_CONTROL_SHADER;
  } else if(is_ext(".tese")) {
    type = GL_TESS_EVALUATION_SHADER;
  } else if(is_ext(".geom")) {
    type = GL_GEOMETRY_SHADER;
  } else if(is_ext(".frag")) {
    type = GL_FRAGMENT_SHADER;
  } else if(is_ext(".comp")) {
    type = GL_COMPUTE_SHADER;
  }
  // else type == 0
}

ShaderProgram::Shader::~Shader()
{}

bool ShaderProgram::Shader::is_ext(const std::string &&ext) {
  if(ext.length() > filename.length())
    return false;
  size_t f=filename.length(),e=ext.length();
  return filename.substr(f-e, e) == ext;
}

size_t ShaderProgram::Shader::file_length() {
  struct stat st;
  stat(filename.c_str(), &st);
  return st.st_size;
}

char *ShaderProgram::Shader::load_text_file() {
  size_t size = file_length() + 1;
  char *text = (char *)malloc(size * sizeof(char));
  assert(text != NULL);

  FILE *file = fopen(filename.c_str(), "r");
  assert(file != NULL);

  char *t = text;
  while((*t = fgetc(file)) != EOF) {
    ++t;
  }
  *t = '\0';

  fclose(file);
  return text;
}

void ShaderProgram::Shader::Compile() {
  id = glCreateShader(type); GLERROR
  char *source_code = load_text_file();
  ASSERT(source_code != NULL);
  glShaderSource(id, 1, &source_code, NULL); GLERROR
  glCompileShader(id); GLERROR
  free(source_code);
}

void ShaderProgram::compile_program() {
  for(auto &s : shaders) {
    s.Compile();
  }
  program = glCreateProgram(); GLERROR
  for(auto &s : shaders) {
    glAttachShader(program, s.id); GLERROR
  }
  glLinkProgram(program); GLERROR

  for(auto &s : shaders) {
    glDeleteShader(s.id); GLERROR
  }
}


ShaderProgram::ShaderProgram(std::vector <std::string> &&fnames):
  shaders()
{
  for(size_t i = 0; i < fnames.size(); ++i) {
    shaders.push_back(Shader(fnames[i]));
  }
}

ShaderProgram::~ShaderProgram()
{}

GLuint ShaderProgram::id() const {
  return program;
}

void ShaderProgram::Use() {
  glUseProgram(id()); GLERROR
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
