#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "Shader.hpp"

class Camera {
  GLuint u_rotation = 0;
  Camera(glm::mat4 view);
  ~Camera();
  static Camera *instance;
public:
  glm::vec3 cam_at = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::mat4 view;
  void AttachToShader(ShaderProgram &program, const char *symbol);
  void Update();
  static Camera *inst();
  static void setup();
};
