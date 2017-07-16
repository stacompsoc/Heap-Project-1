#include "ShaderAttrib.hpp"
#include "Debug.hpp"

gl::Attrib::Attrib()
{}

gl::Attrib::Attrib(const char *loc):
  location(loc)
{}

gl::Attrib::~Attrib()
{}

void gl::Attrib::Init(GLenum vbotype) {
  type = vbotype;
  glGenBuffers(1, &vbo); GLERROR
}

GLuint gl::Attrib::get_id() {
  return vbo;
}

GLuint gl::Attrib::get_loc(GLuint program_id) {
  ASSERT(location != "");
  GLuint loc = glGetAttribLocation(program_id, location.c_str()); GLERROR
  return loc;
}

void gl::Attrib::Bind() {
  glBindBuffer(type, vbo); GLERROR
}

template <GLint TYPE>
void gl::Attrib::Unbind() {
  glBindBuffer(TYPE, 0); GLERROR
}
template void gl::Attrib::Unbind<GL_ARRAY_BUFFER>();

void gl::Attrib::Clear() {
  glDeleteBuffers(1, &vbo); GLERROR
}
