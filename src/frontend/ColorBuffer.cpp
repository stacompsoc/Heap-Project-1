#include "ColorBuffer.hpp"
#include "Log.hpp"

ColorBuffer::ColorBuffer()
{}

ColorBuffer::~ColorBuffer()
{}

void ColorBuffer::Init(const GLfloat *buffer) {
  glGenBuffers(1, &vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), buffer, GL_STATIC_DRAW); GLERROR
}

void ColorBuffer::Clear() {
  glDeleteBuffers(1, &vbo); GLERROR
}
