#pragma once

#include "Triangle.hpp"
#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Shape.hpp"
#include <glm/glm.hpp>

class Object {
protected:
  Uniform<MAT4>u_model;
  Shape &shape;
public:
  ShaderProgram &program;
  bool is_visible = true;
  size_t texture_id;
  glm::mat4
    scale,
    axis_rotation,
    rotate,
    translate;
  glm::mat4
    model_mat;
  float deg_spin;
  float spin;
public:
  bool has_changed = true;
  bool need_to_update = true;
public:
  Object(
    size_t shape_id, ShaderProgram &program,
    size_t texture_id = UINT_MAX,
    double size = 0.5,
    double x = 0., double y = 0., double z = 0.,
    float deg_spin = 0., float deg = 0.0
  );
  ~Object();
  virtual void Init();
  virtual void Update();
  void Scale(float scaling);
  void Scale(float sx, float sy, float sz);
  void SetScale(float scaling);
  void SetScale(float sx, float sy, float sz);
  void RotateAxis();
  void Rotate(float x, float y, float z, float deg);
  void SetRotation(float x, float y, float z, float deg);
  void Translate(float x, float y, float z);
  void Move(float x, float y, float z);
  virtual void AttachToShader();
  virtual void Draw();
  virtual void Clear();
};
