#include "ColorBuffer.hpp"
#include "Debug.hpp"

gl::ColorBuffer::ColorBuffer()
{}

gl::ColorBuffer::~ColorBuffer()
{}

void gl::ColorBuffer::Init(const GLfloat *buffer) {
  glGenBuffers(1, &vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), buffer, GL_STATIC_DRAW); GLERROR
}

void gl::ColorBuffer::Clear() {
  glDeleteBuffers(1, &vbo); GLERROR
}
