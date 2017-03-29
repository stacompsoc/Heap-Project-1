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
  const int PRECISION = 16;
  const double step = M_PI / double(PRECISION);
  size_t color = 2 + rand() % 6;
  /* size_t color = 0; */
  for(double dyx = 0.; dyx < M_PI; dyx += step) {
    for(double dzx = 0.; dzx < 2.*M_PI; dzx += step) {
      color = 2 + rand() % 6;
      glm::vec3
        &&a = position + Camera::point_on_sphere(dyx, dzx) * radius,
        &&b = position + Camera::point_on_sphere(dyx + step, dzx + step) * radius,
        &&c = position + Camera::point_on_sphere(dyx + step, dzx) * radius;
      add_triangle(a, b, c, color);
      a = position + Camera::point_on_sphere(dyx, dzx) * radius;
      b = position + Camera::point_on_sphere(dyx, dzx + step) * radius;
      c = position + Camera::point_on_sphere(dyx + step, dzx + step) * radius;
      add_triangle(a, b, c, color);
    }
  }
}

void Sphere::add_triangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, size_t color) {
  gl_log("add triangle\n");
  GLfloat buffer[9];
  gl_log("%.2f,%.2f,%.2f\n", a.x,a.y,a.z);
  gl_log("%.2f,%.2f,%.2f\n", b.x,b.y,b.z);
  gl_log("%.2f,%.2f,%.2f\n", c.x,c.y,c.z);
  memcpy(buffer, glm::value_ptr(a), sizeof(GLfloat) * 3);
  memcpy(buffer + 3, glm::value_ptr(b), sizeof(GLfloat) * 3);
  memcpy(buffer + 6, glm::value_ptr(c), sizeof(GLfloat) * 3);
  triangles.push_back(Triangle());
  triangles.back().Init(buffer, color);
}
