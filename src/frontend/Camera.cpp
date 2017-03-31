#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(float width, float height)
{
  SetScale(1.0f);
  SetPosition(0, 0, 0.0);
  SetRotation(0, 1, 0, 00.0f);
  Update();
}

Camera::~Camera()
{}

void Init() {
}

void Camera::AttachToShader(ShaderProgram &program) {
  ASSERT(program.id() != 0);
  u_camera = glGetUniformLocation(program.id(), "camera"); GLERROR;
}

void Camera::SetPosition(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z));
}

void Camera::MovePosition(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z)) * translate;
}

void Camera::SetRotation(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z));
}

void Camera::Rotate(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z)) * rotate;
}

void Camera::SetScale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling));
}

void Camera::ChangeScale(float diff) {
  scale = glm::scale(glm::vec3(diff, diff, diff)) * scale;
}

void Camera::Update() {
  cameramat = translate * rotate * scale;
}

void Camera::UniformUpdate() {
  glUniformMatrix4fvARB(u_camera, 1 , GL_FALSE, glm::value_ptr(cameramat)); GLERROR
}

void Camera::Clear() {
}
