#include "Moveable.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Moveable::Scale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling)) * scale;
  has_changed = true;
}

void Moveable::Scale(float sx, float sy, float sz) {
  scale = glm::scale(glm::vec3(sx, sy, sz)) * scale;
  has_changed = true;
}

void Moveable::SetScale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling));
  has_changed = true;
}

void Moveable::SetScale(float sx, float sy, float sz) {
  scale = glm::scale(glm::vec3(sx, sy, sz));
  has_changed = true;
}

glm::vec4 Moveable::GetScale() {
  return glm::vec4(scale[0][0], scale[1][1], scale[2][2], scale[3][3]);
}

void Moveable::SetPosition(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z));
  has_changed = true;
}

glm::vec4 Moveable::GetPosition() {
  return translate * glm::vec4(1.0f);
}

void Moveable::MovePosition(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z)) * translate;
  has_changed = true;
}

void Moveable::Rotate(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z)) * rotate;
  has_changed = true;
}

void Moveable::SetRotation(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z));
  has_changed = true;
}
