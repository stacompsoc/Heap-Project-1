#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::mat4 view_matrix, glm::mat4 projection_matrix):
  view_matrix(view_matrix), projection_matrix(projection_matrix)
{}

Camera::~Camera()
{}

glm::vec3 Camera::point_on_sphere(double dyx, double dzx) {
  //sin(dyx) is a radius of unitary zx circle
  return glm::vec3(
    /*x*/sin(dyx)*cos(dzx),
    /*y*/cos(dyx),
    /*z*/sin(dyx)*sin(dzx)
  );
}

void Camera::AttachToShader(ShaderProgram &program) {
  ASSERT(program.id() != 0);
  u_view = glGetUniformLocation(program.id(), "view"); GLERROR
  u_projection = glGetUniformLocation(program.id(), "projection"); GLERROR
}

void Camera::Update() {
  glm::vec3 new_view = point_on_sphere(yx, zx) * dist;
  view_matrix = glm::lookAt(
    new_view,
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  );
  glUniformMatrix4fvARB(u_view, 1 , GL_FALSE, glm::value_ptr(view_matrix)); GLERROR
  glUniformMatrix4fvARB(u_projection, 1 , GL_FALSE, glm::value_ptr(projection_matrix)); GLERROR
}

Camera *Camera::inst() {
  return instance;
}

Camera *Camera::instance = NULL;
void Camera::Setup(size_t width, size_t height) {
  ASSERT(inst() == NULL);
  instance = new Camera(glm::lookAt(
      glm::vec3(0.0f, 0.0f, 1.0f), // camera is at (0, 0, 1)
      glm::vec3(0.0f, 0.0f, 0.0f), // camera looks at (0, 0, 0)
      glm::vec3(0.0f, 1.0f, 0.0f) // head position
  ), glm::perspective(
    90.0f, // horizontal field of view
    float(width)/float(height), // aspect ratio, window width/height
    0.0f, // near clipping plane, keep it as high as possible
    10000.0f // far clipping placem keep it as low as possible
  ));
}
