#include "Sphere.hpp"
#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

Sphere::Sphere():
  Shape()
{}

Sphere::~Sphere()
{}

glm::vec3 point_on_sphere(double dyx, double dzx) {
  //sin(dyx) is a radius of unitary zx circle
  return glm::vec3(
    /*x*/sin(dyx)*cos(dzx),
    /*y*/cos(dyx),
    /*z*/sin(dyx)*sin(dzx)
  );
}

void Sphere::Init() {
  const double step = M_PI / double(DIM);
  int index = 0;
  /* glm::vec3 p(1., 1., 1.); */
  #define p
  for(double dyx = 0.; dyx < M_PI; dyx += step) {
    for(double dzx = 0.; dzx < 2.*M_PI; dzx += step) {
      glm::vec3
        &&a = point_on_sphere(dyx, dzx),
        &&b = point_on_sphere(dyx + step, dzx + step),
        &&c = point_on_sphere(dyx + step, dzx);
      add_triangle(p+a, p+b, p+c, index, true);
      ++index;
      a = point_on_sphere(dyx, dzx);
      b = point_on_sphere(dyx, dzx + step);
      c = point_on_sphere(dyx + step, dzx + step);
      add_triangle(p+a, p+b, p+c, index, true);
      ++index;
    }
  }
  #undef p
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
    float xstep = 0.5f / float(DIM);
    float tx0 = float(x) / float(2 * DIM);
    float tx1 = tx0 + xstep;
    float ystep = 1.0f / float(DIM);
    float ty0 = float(y) / float(DIM);
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
