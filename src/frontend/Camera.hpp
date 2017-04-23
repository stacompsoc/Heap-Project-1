#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Moveable.hpp"

class Camera : public Moveable {
  Uniform<MAT4>
    u_camera;
  glm::mat4
    projection,
    cameramat;
public:
  /* bool has_changed = true; */
  bool need_to_update = true;
  Camera();
  ~Camera();
  void WindowResized(float new_width, float new_height);
  void AttachToShader(ShaderProgram &program);
  void Init();
  void Update();
  void Clear();
};
