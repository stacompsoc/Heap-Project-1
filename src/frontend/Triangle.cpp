#include "Triangle.hpp"
#include "Log.hpp"

#include <cstring>

Triangle::vertexbuffer::vertexbuffer(GLfloat *buffer):
  buffer(buffer)
{}

Triangle::vertexbuffer::~vertexbuffer()
{}

Triangle::Triangle():
  vb(NULL), cb_vbo(0)
{}

Triangle::~Triangle() {
}

void Triangle::Init(GLfloat *positions, size_t color_id) {
  vb.buffer = new GLfloat[9];
  memcpy(vb.buffer, positions, sizeof(GLfloat) * 9);
  cb_vbo = Storage::inst()->colors()[color_id].vbo;
  init_vertices();
  init_array_object();
}

void Triangle::init_vertices() {
  ASSERT(vb.vbo == 0);
  glGenBuffers(1, &vb.vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vb.vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vb.buffer, GL_STATIC_DRAW); GLERROR
}

void Triangle::init_array_object() {
  glGenVertexArrays(1, &vao); GLERROR
  // attach position buffer and color buffer to this triangle's vertex array object
  glBindVertexArray(vao); GLERROR

  glBindBuffer(GL_ARRAY_BUFFER, vb.vbo); GLERROR
  glEnableVertexAttribArray(0); GLERROR // layout(location == 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR

  glBindBuffer(GL_ARRAY_BUFFER, cb_vbo); GLERROR
  glEnableVertexAttribArray(1); GLERROR // layout(location == 1)
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR
}

void Triangle::disable_vao_attribs() {
  glDisableVertexAttribArray(0); GLERROR
  glDisableVertexAttribArray(1); GLERROR
}

void Triangle::ChangePosition() {
  glBindVertexArray(vao); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vb.vbo); GLERROR
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR
}

void Triangle::ChangeColor(size_t color_id) {
  cb_vbo = Storage::inst()->colors()[color_id].vbo;
  glBindVertexArray(vao); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, cb_vbo); GLERROR
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR
}

void Triangle::Draw() const {
  ASSERT(vao != 0);
  glBindVertexArray(vao); GLERROR
  glDrawArrays(GL_TRIANGLES, 0, 3); GLERROR
}

void Triangle::Clear() {
  ASSERT(vb.vbo != 0);
  glDeleteBuffers(1, &vb.vbo); GLERROR
  glDeleteVertexArrays(1, &vao); GLERROR
  delete [] vb.buffer;
}
