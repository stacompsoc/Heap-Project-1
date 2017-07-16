#include "Object.hpp"
#include "Debug.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Storage.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <climits>

size_t Object::NOTEXTURE = UINT_MAX;
Object::Object(
  size_t shape_id,
  size_t texture_id,
  gl::Program &program,
  glm::vec3 position,
  glm::vec3 size,
  float deg_spin, float spin
):
  shape(*Sprite<Shape *>::Access(shape_id)),
  texture_id(texture_id),
  program(program),
  deg_spin(deg_spin),
  spin(spin),
  u_model("model")
{
  axis_rotation = glm::mat4(1.0f);
  SetScale(size.x, size.y, size.z);
  if(shape_id == Storage::SPHERE) {
    SetRotation(0, 1, 0, -90);
  }
  Rotate(0, 0, 1, deg_spin);
  SetPosition(position.x, position.y, position.z);
}

Object::~Object()
{}

void Object::Init() {
}

void Object::RotateAxis() {
  axis_rotation = glm::rotate(glm::radians(spin), glm::vec3(0, 1, 0)) * axis_rotation;
  has_changed = true;
}

void Object::AttachToShader() {
  u_model.set_id(program.id());
}

void Object::Update() {
  if(has_changed) {
    model_mat = translate * rotate * axis_rotation * scale;
    has_changed = false;
  }
  if(need_to_update) {
    u_model.set_data(model_mat);
  }
}

void Object::Draw() {
  /* size_t x=clock(); */
  if(spin)
    RotateAxis();
  program.Use();
  if(!is_visible)
    return;
  if(texture_id != NOTEXTURE && need_to_update) {
    Sprite<gl::Texture>::Access(texture_id).AttachToShader(program);
    Sprite<gl::Texture>::Access(texture_id).Bind();
  }
  AttachToShader();
  Update();
  shape.Draw();
#ifdef NDEBUG
  if(texture_id != UINT_MAX) {
    Sprite<gl::Texture>::Access(texture_id).Unbind();
  }
  gl::Program::Unuse();
#endif
  /* size_t y=clock();printf("objdraw %lu\n", y-x);x=clock(); */
}

void Object::Clear() {
}
