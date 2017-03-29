#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "Shader.hpp"

class Camera {
  GLuint u_view = 0, u_projection = 0;
  glm::mat4 view_matrix;
  glm::mat4 projection_matrix;
public:
  double zx = M_PI/2., yx = M_PI/2.;
  float dist = 1.0f;
  Camera(float width, float height);
  ~Camera();
  static glm::vec3 point_on_sphere(double, double);
  void AttachToShader(ShaderProgram &program);
  void Init();
  void Update();
  void Clear();
};
