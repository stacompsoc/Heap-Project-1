#include "ShaderAttrib.hpp"
#include "Debug.hpp"

gl::ShaderAttrib::ShaderAttrib()
{}

gl::ShaderAttrib::ShaderAttrib(const char *loc):
  location(loc)
{}

gl::ShaderAttrib::~ShaderAttrib()
{}

void gl::ShaderAttrib::Init(GLenum vbotype) {
  type = vbotype;
  glGenBuffers(1, &vbo); GLERROR
}

void gl::ShaderAttrib::Bind() {
  glBindBuffer(type, vbo); GLERROR
}

GLuint gl::ShaderAttrib::get_id() {
  return vbo;
}

GLuint gl::ShaderAttrib::get_loc(GLuint program_id) {
  ASSERT(location != "");
  GLuint loc = glGetAttribLocation(program_id, location.c_str()); GLERROR
  return loc;
}

void gl::ShaderAttrib::Clear() {
  glDeleteBuffers(1, &vbo); GLERROR
}
