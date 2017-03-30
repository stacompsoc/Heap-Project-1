#include "Object.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <climits>

Object::Object(
  Shape &shape, ShaderProgram &program,
  size_t texture_id,
  double size, double x, double y, double z
):
  shape(shape),
  program(program),
  texture_id(texture_id)
{
  SetScale(size);
  SetRotation(0, 1, 0, -M_PI/2);
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

void Object::Rotate(float x, float y, float z, float rad) {
  rotate = glm::rotate(rad, glm::vec3(x, y, z)) * rotate;
}

void Object::SetRotation(float x, float y, float z, float rad) {
  rotate = glm::rotate(rad, glm::vec3(x, y, z));
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
  Rotate(.1, 1, .1, -M_PI/70.);
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
