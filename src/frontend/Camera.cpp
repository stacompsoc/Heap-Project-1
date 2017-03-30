#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(float width, float height):
  projection_matrix(glm::perspective(
    60.0f, // horizontal field of view
    float(width)/float(height), // aspect ratio, window width/height
    0.0f, // near clipping plane, keep it as high as possible
    1000.0f // far clipping placem keep it as low as possible
  ))
{
  SetCameraPosition(0, 0, 0);
  UpdateViewMatrix();
}

Camera::~Camera()
{}

void Camera::AttachToShader(ShaderProgram &program) {
  ASSERT(program.id() != 0);
  u_camera = glGetUniformLocation(program.id(), "camera"); GLERROR;
}

void Camera::MoveCamera(float x, float y, float z) {
  campos.x+=x,campos.y+=y,campos.z+=z;
}

void Camera::SetCameraPosition(float x, float y, float z) {
  campos.x=x,campos.y=y,campos.z=z;
}

void Camera::SetCameraLookAt(float x, float y, float z) {
  lookat.x=x,lookat.y=y,lookat.z=z;
}

void Camera::UpdateViewMatrix() {
  view_matrix = glm::lookAt(campos, lookat, upvector);
}

void Camera::Update() {
  view_matrix = glm::lookAt(
    campos,
    lookat,
    glm::vec3(0.0f, 1.0f, 0.0f)
  );
  cameramat = view_matrix;
  glUniformMatrix4fvARB(u_camera, 1 , GL_FALSE, glm::value_ptr(cameramat)); GLERROR
}

void Init() {
}

void Camera::Clear() {
}
