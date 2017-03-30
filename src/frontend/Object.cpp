#include "Object.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <climits>

Object::Object(
  Shape &shape, ShaderProgram &program,
  size_t texture_id,
  double size, double x, double y, double z,
  float deg_spin
):
  shape(shape),
  program(program),
  texture_id(texture_id),
  deg_spin(deg_spin)
{
  SetScale(size);
  SetRotation(0, 1, 0, -90);
  Rotate(0, 0, 1, deg_spin);
  Translate(x, y, z);
}

Object::~Object()
{}

void Object::Init() {
}

void Object::Update() {
  model_mat = translate * rotate * scale;
  glUniformMatrix4fvARB(u_object, 1 , GL_FALSE, glm::value_ptr(model_mat)); GLERROR
}

void Object::Scale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling)) * scale;
}

void Object::SetScale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling));
}

void Object::Rotate(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z)) * rotate;
}

void Object::SetRotation(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z));
}

void Object::Move(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z)) * translate;
}

void Object::Translate(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z));
}

void Object::AttachToShader() {
  u_object = glGetUniformLocation(program.id(), "model"); GLERROR
}

void Object::Draw() {
  if(deg_spin) {
    Rotate(-deg_spin/90., 1, -deg_spin/90., 5.0);
  }
  program.Use();
  if(!is_visible)
    return;
  if(texture_id != UINT_MAX) {
    Storage::inst()->textures()[texture_id].AttachToShader(program);
    Storage::inst()->textures()[texture_id].Bind();
  }
  AttachToShader();
  Update();
  shape.Draw();
  if(texture_id != UINT_MAX) {
    Storage::inst()->textures()[texture_id].Unbind();
  }
}

void Object::Clear() {
}
