#include "Sphere.hpp"
#include "Log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <cmath>

Sphere::Sphere(glm::vec3 position, GLfloat r):
  position(position), radius(r), tessellation(0)
{}

Sphere::~Sphere()
{}

static glm::vec3 point_on_sphere(double dyz, double dxz) {
  return glm::vec3(sin(dyz) + cos(dxz), cos(dyz), sin(dxz));
}
void Sphere::Init() {
  const double PRECISION = 4.;
  const double step = (M_PI/2.) / PRECISION;
  for(double dyz = 0.; dyz < M_PI/2; dyz += step) {
    for(double dxz = 0.; dxz < M_PI/2; dxz += step) {
      const glm::vec3 &a = position + point_on_sphere(dyz, dxz) * radius;
      const glm::vec3 &b = position + point_on_sphere(dyz + step, dxz) * radius;
      const glm::vec3 &c = position + point_on_sphere(dyz + step, dxz) * radius;
      add_triangle(a, b, c);
    }
  }
}

void Sphere::add_triangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c) {
  GLfloat buffer[9];
  memcpy(buffer, glm::value_ptr(a), sizeof(GLfloat) * 3);
  memcpy(buffer, glm::value_ptr(b), sizeof(GLfloat) * 3);
  memcpy(buffer, glm::value_ptr(c), sizeof(GLfloat) * 3);
  tessellation.push_back(Triangle());
  tessellation.back().Init(buffer, 0);
}

void Sphere::Draw() {
  for(auto &t : tessellation)
    t.Draw();
}

void Sphere::Clear() {
  for(auto &t : tessellation)
    t.Clear();
  tessellation.clear();
}
