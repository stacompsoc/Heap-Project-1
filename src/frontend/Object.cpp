#include "Object.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <climits>

Object::Object(Shape &shape, ShaderProgram &program, size_t texture_id, double size):
  shape(shape),
  program(program),
  u_scale(0), u_rotate(0), u_translate(0),
  rotate(glm::rotate(
    00.0f, // rotation degree
    glm::vec3(1.0f, 1.0f, 1.0f)
  )),
  texture_id(texture_id)
{
  Move(0.0f, 0.0f, 0.0f);
  SetScale(size);
}

Object::~Object()
{}

void Object::Init() {
}

void Object::Update() {
  glUniformMatrix4fvARB(u_scale, 1 , GL_FALSE, glm::value_ptr(scale)); GLERROR
  glUniformMatrix4fvARB(u_rotate, 1 , GL_FALSE, glm::value_ptr(rotate)); GLERROR
  glUniformMatrix4fvARB(u_translate, 1 , GL_FALSE, glm::value_ptr(translate)); GLERROR
}

void Object::SetScale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling));
}

void Object::Move(float x, float y, float z) {
  Move(glm::vec3(x, y, z));
}

void Object::Move(glm::vec3 pos) {
  translate = glm::translate(pos);
}

void Object::AttachToShader() {
  u_scale = glGetUniformLocation(program.id(), "scale"); GLERROR
  u_rotate = glGetUniformLocation(program.id(), "rotate"); GLERROR
  u_translate = glGetUniformLocation(program.id(), "translate"); GLERROR
}

void Object::Draw() {
  if(!is_visible)
    return;
  if(texture_id != UINT_MAX) {
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
