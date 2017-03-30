#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "Shader.hpp"

class Camera {
  GLuint u_camera = 0;
  glm::vec3
    campos,
    lookat,
    upvector = glm::vec3(0, 1, 0);
  glm::mat4
    view_matrix,
    projection_matrix;
  glm::mat4
    cameramat;
public:
  double zx = M_PI/2., yx = M_PI/2.;
  float dist = 1.0f;
  Camera(float width, float height);
  ~Camera();
  void AttachToShader(ShaderProgram &program);
  void Init();
  void MoveCamera(float x, float y, float z);
  void SetCameraPosition(float x, float y, float z);
  void SetCameraLookAt(float x, float y, float z);
  void UpdateViewMatrix();
  void Update();
  void Clear();
};
