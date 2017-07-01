#pragma once

#include <glm/glm.hpp>

#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Shape.hpp"
#include "Moveable.hpp"

class Object : public Moveable {
protected:
  gl::Uniform<gl::UniformType::MAT4>u_model;
  Shape &shape;
  gl::ShaderProgram &program;
  size_t texture_id;
  bool is_visible = true;
public:
  glm::mat4
    axis_rotation;
  glm::mat4
    model_mat;
  float deg_spin;
  float spin;
public:
  /* bool has_changed = true; */
  bool need_to_update = true;
public:
  static size_t NOTEXTURE;
  Object(
    size_t shape_id,
    size_t texture_id,
    gl::ShaderProgram &program,
    glm::vec3 position,
    glm::vec3 size,
    float deg_spin = 0., float deg = 0.0
  );
  ~Object();
  virtual void Init();
  void RotateAxis();
  virtual void AttachToShader();
  virtual void Update();
  virtual void Draw();
  virtual void Clear();
};
