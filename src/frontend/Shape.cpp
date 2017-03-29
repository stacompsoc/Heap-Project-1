#include "Shape.hpp"
#include "Log.hpp"

Shape::Shape():
  triangles(0)
{}

Shape::~Shape()
{}

void Shape::Draw() {
  for(auto &t : triangles)
    t.Draw();
}

void Shape::Clear() {
  for(auto &t : triangles)
    t.Clear();
  triangles.clear();
}
