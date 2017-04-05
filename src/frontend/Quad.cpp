#include "Quad.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Quad::Quad():
  Shape()
{}

Quad::~Quad()
{}

void Quad::Init() {
  glm::vec3
    a(-1, -1, 0),
    b(-1,  1, 0),
    c( 1,  1, 0),
    d( 1, -1, 0);
  AddTriangle(a, b, c, 0, true);
  AddTriangle(c, d, a, 1, true);
}

void Quad::SetTexcoords(size_t index, GLfloat texcoords[6]) {
  if(index == 0) {
    GLfloat tmp[6] = {
      0, 0,
      0, 1,
      1, 1,
    };
    memcpy(texcoords, tmp, 6 * sizeof(GLfloat));
  } else {
    GLfloat tmp[6] = {
      1, 1,
      1, 0,
      0, 0,
    };
    memcpy(texcoords, tmp, 6 * sizeof(GLfloat));
  }
  gl_log("%.2f,%.2f\n", texcoords[0], texcoords[1]);
  gl_log("%.2f,%.2f\n", texcoords[2], texcoords[3]);
  gl_log("%.2f,%.2f\n", texcoords[4], texcoords[5]);
}

void Quad::AddTriangle(
  const glm::vec3 &a,
  const glm::vec3 &b,
  const glm::vec3 &c,
  size_t index,
  bool is_textured)
{
  GLfloat buffer[9];
  memcpy(buffer, glm::value_ptr(a), sizeof(GLfloat) * 3);
  memcpy(buffer + 3, glm::value_ptr(b), sizeof(GLfloat) * 3);
  memcpy(buffer + 6, glm::value_ptr(c), sizeof(GLfloat) * 3);
  triangles.push_back(Triangle());
  if(!is_textured) {
    gl_log("is textured %d\n", is_textured);
    size_t color = 0;
    triangles.back().Init(buffer, color);
  } else {
    gl_log("is textured %d\n", is_textured);
    GLfloat texcoords[6];
    SetTexcoords(index, texcoords);
    triangles.back().Init(buffer, texcoords);
  }
}

void Quad::Draw() {
  for(auto &t : triangles)
    t.Draw();
}

void Quad::Clear() {
  for(auto &t : triangles)
    t.Clear();
}
