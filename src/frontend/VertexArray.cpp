#include "VertexArray.hpp"
#include "Debug.hpp"

GLuint gl::VertexArray::last_vao = 0;
gl::VertexArray::VertexArray()
{}

gl::VertexArray::~VertexArray()
{}

void gl::VertexArray::Init() {
  glGenVertexArrays(1, &id); GLERROR
}

GLuint gl::VertexArray::get_id() const {
  return id;
}

void gl::VertexArray::Bind() {
  if(last_vao == id)
    return;
  glBindVertexArray(id); GLERROR
  last_vao = id;
}

void gl::VertexArray::Enable(gl::Attrib &attrib) {
  glEnableVertexAttribArray(attribs.size()); GLERROR
  attribs.push_back(attrib);
}

void gl::VertexArray::Unbind() {
  glBindVertexArray(0); GLERROR
  last_vao = 0;
}

void gl::VertexArray::Clear() {
  glDeleteVertexArrays(1, &id); GLERROR
}
