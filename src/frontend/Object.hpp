#pragma once

#include "Triangle.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include <glm/glm.hpp>

struct Object {
protected:
  GLuint u_scale;
  GLuint u_rotate;
  GLuint u_translate;
  Shape &shape;
public:
  ShaderProgram &program;
  bool is_visible = true;
  size_t texture_id;
  glm::mat4 scale;
  glm::mat4 rotate;
  glm::mat4 translate;
public:
  Object(Shape &shape, ShaderProgram &program, size_t texture_id = UINT_MAX,
         double size = 0.5);
  ~Object();
  virtual void Init();
  virtual void Update();
  void SetScale(float scaling);
  void Move(float x, float y, float z);
  void Move(glm::vec3 pos);
  virtual void AttachToShader();
  virtual void Draw();
  virtual void Clear();
};
