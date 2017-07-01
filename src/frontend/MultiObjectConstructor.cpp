#include "MultiObjectConstructor.hpp"
#include "Debug.hpp"
#include "Space.hpp"
#include "Storage.hpp"

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

void MultiObjectConstructor::Spawn(size_t shape_id, size_t texture_id, gl::ShaderProgram &program) {
  space->AddObject(
    Object(
      shape_id, texture_id, program,
      position, size,
      rot, spin
    )
  );
}

void MultiObjectConstructor::SpawnPlanet(size_t texture_id, gl::ShaderProgram &program) {
  Spawn(Storage::SPHERE, texture_id, program);
}

void MultiObjectConstructor::SpawnClouds(size_t texture_id, gl::ShaderProgram &program) {
  glm::vec3 cur_size = size;
  glm::vec3 new_size = cur_size*1.01f;
  SetSize(new_size.x, new_size.y, new_size.z);
  Spawn(Storage::SPHERE, texture_id, program);
  SetSize(cur_size.x, cur_size.y, cur_size.z);
}

void MultiObjectConstructor::StartObject() {
  space->AddMultiObject();
}
