#pragma once

#include <glm/glm.hpp>
#include "incgraphics.h"

#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Moveable.hpp"

class Camera : public Moveable {
  Uniform<MAT4>
    u_camera;
  /* glm::mat4 */
  /*   translate, */
  /*   rotate, */
  /*   scale; */
  glm::mat4
    cameramat;
public:
  /* bool has_changed = true; */
  bool need_to_update = true;
  Camera(float width, float height);
  ~Camera();
  void AttachToShader(ShaderProgram &program);
  void Init();
  void ChangeScale(float diff);
  void Update();
  void Clear();
};
