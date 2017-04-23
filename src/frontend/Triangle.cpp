#include "Triangle.hpp"
#include "Debug.hpp"
#include "Logger.hpp"
#include "ColorBuffer.hpp"
#include "Sprite.hpp"

#include <cstring>
#include <stdexcept>

Triangle::vertexbuffer::vertexbuffer()
{}

Triangle::vertexbuffer::~vertexbuffer()
{}

Triangle::texcoordbuffer::texcoordbuffer()
{}

Triangle::texcoordbuffer::~texcoordbuffer()
{}

Triangle::Triangle()
{}

Triangle::~Triangle()
{}

void Triangle::Init(GLfloat *positions, size_t color_id) {
  init_vertices(positions);
  cb_vbo = Sprite<ColorBuffer>::Access(color_id).vbo;
  init_array_object();
}

void Triangle::Init(GLfloat *positions, GLfloat *texcoords) {
  tex.is_enabled = true;
  init_vertices(positions);
  init_texcoords(texcoords);
  init_array_object();
}

void Triangle::init_vertices(GLfloat *buffer) {
  glGenBuffers(1, &vb.vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vb.vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), buffer, GL_STATIC_DRAW); GLERROR
}

void Triangle::init_texcoords(GLfloat *buffer) {
  ASSERT(tex.vbo == 0);
  glGenBuffers(1, &tex.vbo); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, tex.vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), buffer, GL_STATIC_DRAW); GLERROR
}

void Triangle::init_array_object() {
  vao.Init();
  vao.Bind();

  glBindBuffer(GL_ARRAY_BUFFER, vb.vbo); GLERROR
  glEnableVertexAttribArray(0); GLERROR // layout(location == 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR

  if(tex.is_enabled) {
    glBindBuffer(GL_ARRAY_BUFFER, tex.vbo); GLERROR
    glEnableVertexAttribArray(1); GLERROR // layout(location == 2)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR
    Logger::Info("triangle: vertex array == %d\n", vao.get_id());
  } else {
    glBindBuffer(GL_ARRAY_BUFFER, cb_vbo); GLERROR
    glEnableVertexAttribArray(1); GLERROR // layout(location == 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR
  }
}

void Triangle::disable_vao_attribs() {
  glDisableVertexAttribArray(0); GLERROR
  if(tex.is_enabled) {
    glDisableVertexAttribArray(1); GLERROR
  } else {
    glDisableVertexAttribArray(1); GLERROR
  }
}

void Triangle::ChangePosition() {
  vao.Bind();
  glBindBuffer(GL_ARRAY_BUFFER, vb.vbo); GLERROR
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR
}

void Triangle::ChangeColor(size_t color_id) {
  ASSERT(!tex.is_enabled);
  cb_vbo = Sprite<ColorBuffer>::Access(color_id).vbo;
  vao.Bind();
  glBindBuffer(GL_ARRAY_BUFFER, cb_vbo); GLERROR
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL); GLERROR
}

void Triangle::Draw() {
  vao.Bind();
  glDrawArrays(GL_TRIANGLES, 0, 3); GLERROR
}

void Triangle::Clear() {
  glDeleteBuffers(1, &vb.vbo); GLERROR
  if(tex.is_enabled) {
    glDeleteBuffers(1, &tex.vbo); GLERROR
  }
  /* disable_vao_attribs(); */
  vao.Clear();
}
