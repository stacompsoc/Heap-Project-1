#include "Object.hpp"
#include "Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <climits>

Object::Object(
  size_t shape_id, ShaderProgram &program,
  size_t texture_id,
  double size, double x, double y, double z,
  float deg_spin
):
  shape(*Storage::inst()->shapes()[shape_id]),
  program(program),
  texture_id(texture_id),
  deg_spin(deg_spin),
  u_model("model")
{
  SetScale(size);
  SetRotation(0, 1, 0, -90);
  Rotate(1, 0, 0, deg_spin);
  Translate(x, y, z);
  /* spin = float(rand() % 100) / 10.; */
  spin = 2.5f;
  /* spin = 0.0f; */
}

Object::~Object()
{}

void Object::Init() {
}

void Object::Scale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling)) * scale;
  has_changed = true;
}

void Object::Scale(float sx, float sy, float sz) {
  scale = glm::scale(glm::vec3(sx, sy, sz)) * scale;
  has_changed = true;
}

void Object::SetScale(float scaling) {
  scale = glm::scale(glm::vec3(scaling, scaling, scaling));
  has_changed = true;
}

void Object::SetScale(float sx, float sy, float sz) {
  scale = glm::scale(glm::vec3(sx, sy, sz));
  has_changed = true;
}

void Object::Rotate(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z)) * rotate;
  has_changed = true;
}

void Object::SetRotation(float x, float y, float z, float deg) {
  rotate = glm::rotate(glm::radians(deg), glm::vec3(x, y, z));
  has_changed = true;
}

void Object::SetAxisRotation() {
}

void Object::Move(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z)) * translate;
  has_changed = true;
}

void Object::Translate(float x, float y, float z) {
  translate = glm::translate(glm::vec3(x, y, z));
  has_changed = true;
}

void Object::AttachToShader() {
  u_model.set_id(program.id());
}

void Object::Update() {
  if(has_changed) {
    model_mat = translate * rotate * scale;
    has_changed = false;
  }
  if(need_to_update) {
    u_model.set_data(model_mat);
  }
}

void Object::Draw() {
  if(deg_spin) {
    Rotate(0, 1, 0, spin);
    /* rotate = axis_rotation * rotate; */
  }
  program.Use();
  if(!is_visible)
    return;
  if(texture_id != UINT_MAX && need_to_update) {
    Storage::inst()->textures()[texture_id].AttachToShader(program);
    Storage::inst()->textures()[texture_id].Bind();
  }
  AttachToShader();
  Update();
  /* size_t x=clock(); */
  shape.Draw();
  /* size_t y=clock();printf("objdraw %lu\n", y-x);x=clock(); */
  if(texture_id != UINT_MAX) {
    Storage::inst()->textures()[texture_id].Unbind();
  }
  ShaderProgram::Unuse();
}

void Object::Clear() {
}
