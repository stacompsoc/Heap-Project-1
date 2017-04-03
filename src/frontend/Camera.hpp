#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"

class Camera {
  Uniform<MAT4>
    u_camera;
  glm::mat4
    translate,
    rotate,
    scale;
  glm::mat4
    cameramat;
public:
  bool has_changed = true;
  bool need_to_update = true;
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
  void Clear();
};
