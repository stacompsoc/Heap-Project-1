#pragma once

#include "Triangle.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include <glm/glm.hpp>

class Object {
protected:
  GLuint u_object = 0;
  Shape &shape;
public:
  ShaderProgram &program;
  bool is_visible = true;
  size_t texture_id;
  glm::mat4
    scale,
    rotate,
    translate;
  glm::mat4
    model_mat;
public:
  Object(
    Shape &shape, ShaderProgram &program,
    size_t texture_id = UINT_MAX,
    double size = 0.5, double x = 0., double y = 0., double z = 0.
  );
  ~Object();
  virtual void Init();
  virtual void Update();
  void Scale(float scaling);
  void SetScale(float scaling);
  void Rotate(float x, float y, float z, float rad);
  void SetRotation(float x, float y, float z, float rad);
  void Translate(float x, float y, float z);
  void Move(float x, float y, float z);
  virtual void AttachToShader();
  virtual void Draw();
  virtual void Clear();
};
