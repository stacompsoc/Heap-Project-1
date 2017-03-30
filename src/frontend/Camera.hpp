#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "Shader.hpp"

class Camera {
  GLuint u_camera = 0;
  glm::mat4
    translate,
    rotate,
    scale;
  glm::mat4
    cameramat;
public:
  Camera(float width, float height);
  ~Camera();
  void AttachToShader(ShaderProgram &program);
  void Init();
  void SetScale(float scaling);
  void ChangeScale(float diff);
  void SetRotation(float x, float y, float z, float deg);
  void Rotate(float x, float y, float z, float deg);
  void SetPosition(float x, float y, float z);
  void MovePosition(float x, float y, float z);
  void Update();
  void UniformUpdate();
  void Clear();
};
