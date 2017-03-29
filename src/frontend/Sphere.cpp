#include "Sphere.hpp"
#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

Sphere::Sphere():
  Shape(),
  radius(1.0f)
{}

Sphere::Sphere(glm::vec3 position, GLfloat r):
  Shape(),
  position(position), radius(r)
{}

Sphere::~Sphere()
{}

void Sphere::Init() {
  const double step = M_PI / double(DIM);
  int index = 0;
  for(double dyx = 0.; dyx < M_PI; dyx += step) {
    for(double dzx = 0.; dzx < 2.*M_PI; dzx += step) {
      glm::vec3
        &&a = position + Camera::point_on_sphere(dyx, dzx) * radius,
        &&b = position + Camera::point_on_sphere(dyx + step, dzx + step) * radius,
        &&c = position + Camera::point_on_sphere(dyx + step, dzx) * radius;
      add_triangle(a, b, c, index, true);
      ++index;
      a = position + Camera::point_on_sphere(dyx, dzx) * radius;
      b = position + Camera::point_on_sphere(dyx, dzx + step) * radius;
      c = position + Camera::point_on_sphere(dyx + step, dzx + step) * radius;
      add_triangle(a, b, c, index, true);
      ++index;
    }
  }
}

void Sphere::add_triangle(
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
    size_t
      y = DIM - 1 - (index/2) / (2 * DIM),
      x = (index/2) % (2 * DIM);
    float xstep = 1.0f / float(DIM) / 2.;
    float tx0 = float(x) / float (2 * DIM);
    float tx1 = tx0 + xstep;
    float ystep = 1.0f / float(DIM);
    float ty0 = float(y) / float (DIM);
    float ty1 = ty0 + ystep;
    gl_log("is textured %d\n", is_textured);
    GLfloat cpy[6];
    if(index & 1) {
      GLfloat texcoords[6] = {
        tx0, ty1,
        tx1, ty1,
        tx1, ty0,
      };
      memcpy(cpy, texcoords, 6 * sizeof(GLfloat));
    } else {
      GLfloat texcoords[6] = {
        tx0, ty1,
        tx1, ty0,
        tx0, ty0,
      };
      memcpy(cpy, texcoords, 6 * sizeof(GLfloat));
    }
    gl_log("%.2f,%.2f\n", cpy[0], cpy[1]);
    gl_log("%.2f,%.2f\n", cpy[2], cpy[3]);
    gl_log("%.2f,%.2f\n", cpy[4], cpy[5]);
    triangles.back().Init(buffer, cpy);
  }
}
