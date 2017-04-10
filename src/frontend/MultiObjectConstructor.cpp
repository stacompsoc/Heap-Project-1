#include "MultiObjectConstructor.hpp"
#include "Log.hpp"
#include "Space.hpp"

MultiObjectConstructor::MultiObjectConstructor(Space *space):
  space(space), position(0, 0, 0), size(1, 1, 1)
{}

MultiObjectConstructor::~MultiObjectConstructor()
{}

void MultiObjectConstructor::Move(float x, float y, float z) {
  position += glm::vec3(x, y, z);
}

void MultiObjectConstructor::SetPosition(float x, float y, float z) {
  position = glm::vec3(x, y, z);
}

void MultiObjectConstructor::SetSize(float s) {
  SetSize(s, s, s);
}

void MultiObjectConstructor::SetSize(float x, float y, float z) {
  size = glm::vec3(x, y, z);
}

void MultiObjectConstructor::SetRotation(float r) {
  rot = r;
}

void MultiObjectConstructor::SetSpin(float s) {
  spin = s;
}

void MultiObjectConstructor::Spawn(size_t shape_id, size_t texture_id, ShaderProgram &program) {
  space->AddObject(
    Object(
      shape_id, texture_id, program,
      position, size,
      rot, spin
    )
  );
}

void MultiObjectConstructor::StartObject() {
  space->AddMultiObject();
}
