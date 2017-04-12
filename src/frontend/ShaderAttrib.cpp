#include "ShaderAttrib.hpp"
#include "Log.hpp"

ShaderAttrib::ShaderAttrib()
{}

ShaderAttrib::ShaderAttrib(const char *loc):
  location(loc)
{}

ShaderAttrib::~ShaderAttrib()
{}

void ShaderAttrib::Init(GLenum vbotype) {
  type = vbotype;
  glGenBuffers(1, &vbo); GLERROR
}

void ShaderAttrib::Bind() {
  glBindBuffer(type, vbo); GLERROR
}

GLuint ShaderAttrib::get_id() {
  return vbo;
}

GLuint ShaderAttrib::get_loc(GLuint program_id) {
  ASSERT(location != "");
  GLuint loc = glGetAttribLocation(program_id, location.c_str()); GLERROR
  return loc;
}

void ShaderAttrib::Clear() {
  glDeleteBuffers(1, &vbo); GLERROR
}
