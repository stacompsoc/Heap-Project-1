#include "MultiObject.hpp"

MultiObject::MultiObject(ShaderProgram &program):
  program(program)
{}

MultiObject::~MultiObject()
{}

void MultiObject::Init() {
}

void MultiObject::AddObject(Object &&object) {
  objects.push_back(object);
  objects.back().Init();
}

void MultiObject::Draw() {
  program.Use();
  for(auto &obj : objects) {
    obj.Draw();
  }
}

void MultiObject::Clear() {
}
