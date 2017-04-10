#include "MultiObject.hpp"

MultiObject::MultiObject()
{}

MultiObject::~MultiObject()
{}

size_t MultiObject::Size() const {
  return objects.size();
}

void MultiObject::AddObject(Object object) {
  objects.push_back(object);
}

void MultiObject::Apply(std::function <void (Object &)> &&func) {
  for(auto &obj : objects) {
    func(obj);
  }
}

void MultiObject::Init() {
  Apply([](Object &obj){ obj.Init(); });
}

void MultiObject::Draw() {
  for(auto &obj : objects) {
    obj.need_to_update = true;
    obj.Draw();
  }
}

void MultiObject::Scale(float s) {
  Apply([s](Object &obj){ obj.Scale(s); });
}

void MultiObject::SetScale(float s) {
  Apply([s](Object &obj){ obj.SetScale(s); });
}

void MultiObject::Rotate(float x, float y, float z, float deg) {
  Apply([x, y, z, deg](Object &obj){ obj.Rotate(x, y, z, deg); });
}

void MultiObject::RotateAxis() {
  Apply([](Object &obj) { obj.RotateAxis(); });
}

void MultiObject::MovePosition(float x, float y, float z) {
  Apply([x, y, z](Object &obj){ obj.MovePosition(x, y, z); });
}

void MultiObject::SetPosition(float x, float y, float z) {
  Apply([x, y, z](Object &obj){ obj.SetPosition(x, y, z); });
}

void MultiObject::Clear() {
  while(!objects.empty()) {
    objects.back().Clear();
    objects.pop_back();
  }
}
