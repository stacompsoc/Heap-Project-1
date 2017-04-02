#include "Ring.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Ring::Ring():
  Shape()
{}

Ring::~Ring()
{}

glm::vec3 point_on_circle(float angle) {
  return glm::vec3(cos(angle), 0, sin(angle));
}

void Ring::Init() {
  float ir = .7;
  double step = float(M_PI*2) / DIM;
  size_t index = 0;
  double angle = 0.;
  for(int i = 0; i < DIM; ++i) {
    glm::vec3
      &&a = point_on_circle(angle),
      &&b = point_on_circle(angle + step),
      &&c = a * ir;
    AddTriangle(a, b, c, index, true);
    ++index;
    a = b * ir;
    AddTriangle(c, b, a, index, true);
    ++index;
    angle += step;
  }
}

void Ring::AddTriangle(
  const glm::vec3 &a,
  const glm::vec3 &b,
  const glm::vec3 &c,
  size_t index,
  bool is_textured)
{
  gl_log("add triangle\n");
  GLfloat buffer[9];
  gl_log("%.2f,%.2f,%.2f\n", a.x,a.y,a.z);
  gl_log("%.2f,%.2f,%.2f\n", b.x,b.y,b.z);
  gl_log("%.2f,%.2f,%.2f\n", c.x,c.y,c.z);
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
    size_t x = index / 2;
    ASSERT(x < DIM);
    float xstep = 1. / DIM;
    float tx0 = float(x) / DIM, tx1 = tx0 + xstep;
    GLfloat cpy[6];
    if(index & 1) {
      GLfloat texcoords[6] = {
        tx1, 1,
        tx0, 0,
        tx0, 1,
      };
      memcpy(cpy, texcoords, 6 * sizeof(GLfloat));
    } else {
      GLfloat texcoords[6] = {
        tx1, 0,
        tx0, 0,
        tx1, 1,
      };
      memcpy(cpy, texcoords, 6 * sizeof(GLfloat));
    }
    gl_log("%.2f,%.2f\n", cpy[0], cpy[1]);
    gl_log("%.2f,%.2f\n", cpy[2], cpy[3]);
    gl_log("%.2f,%.2f\n", cpy[4], cpy[5]);
    triangles.back().Init(buffer, cpy);
  }
}
