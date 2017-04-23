#include "VertexArray.hpp"
#include "Debug.hpp"

GLuint VertexArray::last_vao = 0;
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
  if(last_vao == id)
    return;
  glBindVertexArray(id); GLERROR
  last_vao = id;
}

void VertexArray::Unbind() {
  glBindVertexArray(0); GLERROR
  last_vao = 0;
}

void VertexArray::Clear() {
  glDeleteVertexArrays(1, &id); GLERROR
}
