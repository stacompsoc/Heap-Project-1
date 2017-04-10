#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(float width, float height):
  Moveable(),
  u_camera("camera")
{
  SetScale(1.0f);
  SetPosition(0, 0, 0.0);
  SetRotation(0, 1, 0, 00.0f);
}

Camera::~Camera()
{}

void Init() {
}

void Camera::AttachToShader(ShaderProgram &program) {
  ASSERT(program.id() != 0);
  u_camera.set_id(program.id());
}

void Camera::ChangeScale(float diff) {
  scale = glm::scale(glm::vec3(diff, diff, diff)) * scale;
  has_changed = true;
}

void Camera::Update() {
  if(has_changed) {
    cameramat = translate * rotate * scale;
    has_changed = false;
  }
  if(need_to_update) {
    u_camera.set_data(cameramat);
  }
}

void Camera::Clear() {
}
