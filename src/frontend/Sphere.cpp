#include "Sphere.hpp"
#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

Sphere::Sphere(glm::vec3 position, GLfloat r):
  position(position), radius(r), tessellation(0)
{}

Sphere::~Sphere()
{}

#define ASSERT_F(a,b) ASSERT(std::abs((a)-(b)) < 1e-3);
#define ASSERT_V(vec, a,b,c) ASSERT_F((vec).x, (a)); ASSERT_F((vec).y, (b)); ASSERT_F((vec).z, (c));
void Sphere::Init() {
  const int PRECISION = 16;
  const double step = M_PI / double(PRECISION);
  size_t color = 2 + rand() % 6;
  for(double dyx = 0.; dyx < M_PI; dyx += step) {
    for(double dzx = 0.; dzx < 2.*M_PI; dzx += step) {
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
  std::cout << "add triangle" << std::endl;
  GLfloat buffer[9];
  printf("%.2f,%.2f,%.2f\n", a.x,a.y,a.z);
  printf("%.2f,%.2f,%.2f\n", b.x,b.y,b.z);
  printf("%.2f,%.2f,%.2f\n", c.x,c.y,c.z);
  memcpy(buffer, glm::value_ptr(a), sizeof(GLfloat) * 3);
  memcpy(buffer + 3, glm::value_ptr(b), sizeof(GLfloat) * 3);
  memcpy(buffer + 6, glm::value_ptr(c), sizeof(GLfloat) * 3);
  tessellation.push_back(Triangle());
  tessellation.back().Init(buffer, color);
}

void Sphere::Draw() {
  for(auto &t : tessellation) {
    t.Draw();
  }
}

void Sphere::Clear() {
  for(auto &t : tessellation)
    t.Clear();
  tessellation.clear();
}
