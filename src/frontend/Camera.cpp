#include "Camera.hpp"
#include "Debug.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera():
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

void Camera::WindowResized(float new_width, float new_height) {
  if(new_width > new_height)
    projection = glm::ortho(-new_width/new_height, new_width/new_height, -1.0f, 1.0f, 1.0f, -1.0f);
  else if(new_width <= new_height)
    projection = glm::ortho(-1.0f, 1.0f, -new_height/new_width, new_height/new_width, 1.0f, -1.0f);
  has_changed = true;
}

void Camera::AttachToShader(gl::Program &program) {
  ASSERT(program.id() != 0);
  u_camera.set_id(program.id());
}

void Camera::Update() {
  if(has_changed) {
    cameramat = projection * translate * rotate * scale;
    has_changed = false;
  }
  if(need_to_update) {
    u_camera.set_data(cameramat);
  }
}

void Camera::Clear() {
}
