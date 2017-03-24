#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::mat4 view):
  view(view)
{}

Camera::~Camera()
{}

void Camera::AttachToShader(ShaderProgram &program, const char *symbol) {
  u_rotation = glGetUniformLocation(program.id(), symbol); GLERROR
}

void Camera::Update() {
  view = glm::lookAt(
    cam_at,
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  );
  glUniformMatrix4fvARB(u_rotation, 1 , false, glm::value_ptr(view));
}

Camera *Camera::inst() {
  return instance;
}

Camera *Camera::instance = NULL;
void Camera::setup() {
  ASSERT(inst() == NULL);
  instance = new Camera(glm::lookAt(
      glm::vec3(0.0f, 0.0f, 1.0f), // camera is at (0, 0, 1)
      glm::vec3(0.0f, 0.0f, 0.0f), // camera looks at (0, 0, 0)
      glm::vec3(0.0f, 1.0f, 0.0f) // head is up
  ));
}
