#include "VertexArray.hpp"
#include "Log.hpp"

VertexArray::VertexArray()
{}

VertexArray::~VertexArray()
{}

void VertexArray::Init() {
  glGenVertexArrays(1, &id); GLERROR
}

GLuint VertexArray::get_id() const {
  return id;
}

void VertexArray::Bind() {
  glBindVertexArray(id); GLERROR
}

void VertexArray::Unbind() {
  glBindVertexArray(0); GLERROR
}

void VertexArray::Clear() {
  glDeleteVertexArrays(1, &id); GLERROR
}
