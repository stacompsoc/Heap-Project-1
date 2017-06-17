#include "ShaderUniform.hpp"
#include "Debug.hpp"

#include <glm/gtc/type_ptr.hpp>

template<UniformType U>
Uniform<U>::Uniform(const char *loc):
  location(loc)
{}


template <UniformType U>
Uniform<U>::~Uniform()
{}


template <UniformType U>
void Uniform<U>::set_id(GLuint program_id) {
  ASSERT(program_id != 0);
  if(prog_id == program_id)
    return;
  prog_id = program_id;
  id = glGetUniformLocation(program_id, location.c_str()); GLERROR
}

template <UniformType U>
void Uniform<U>::unset_id() {
  prog_id = 0;
}

template <UniformType U>
GLuint Uniform<U>::get_id(GLuint program_id) {
  ASSERT(program_id != 0);
  if(program_id == -1u)
    return id;
  if(prog_id != program_id)
    set_id(program_id);
  return id;
}

template <>
void Uniform<UniformType::INTEGER>::set_data(Uniform<UniformType::INTEGER>::dtype data) {
  ASSERT(prog_id != 0);
  glUniform1i(id, data); GLERROR
}

template <>
void Uniform<UniformType::FLOAT>::set_data(Uniform<UniformType::FLOAT>::dtype data) {
  ASSERT(prog_id != 0);
  glUniform1f(id, data); GLERROR
}

template <>
void Uniform<UniformType::VEC2>::set_data(Uniform<UniformType::VEC2>::dtype data) {
  ASSERT(prog_id != 0);
  glUniform2f(id, data.x, data.y); GLERROR
}

template <>
void Uniform<UniformType::VEC3>::set_data(Uniform<UniformType::VEC3>::dtype data) {
  ASSERT(prog_id != 0);
  glUniform3f(id, data.x, data.y, data.z); GLERROR
}

template <>
void Uniform<UniformType::VEC4>::set_data(Uniform<UniformType::VEC4>::dtype data) {
  ASSERT(prog_id != 0);
  glUniform4f(id, data.x, data.y, data.z, data.t); GLERROR
}

template <>
void Uniform<UniformType::MAT2>::set_data(Uniform<UniformType::MAT2>::dtype data) {
  ASSERT(prog_id != 0);
  glUniformMatrix2fvARB(id, 1 , GL_FALSE, glm::value_ptr(data)); GLERROR
}

template <>
void Uniform<UniformType::MAT3>::set_data(Uniform<UniformType::MAT3>::dtype data) {
  ASSERT(prog_id != 0);
  glUniformMatrix3fvARB(id, 1 , GL_FALSE, glm::value_ptr(data)); GLERROR
}

template <>
void Uniform<UniformType::MAT4>::set_data(Uniform<UniformType::MAT4>::dtype data) {
  ASSERT(prog_id != 0);
  glUniformMatrix4fvARB(id, 1 , GL_FALSE, glm::value_ptr(data)); GLERROR
}

template <>
void Uniform<UniformType::SAMPLER2D>::set_data(Uniform<UniformType::SAMPLER2D>::dtype data) {
  ASSERT(prog_id != 0);
  glUniform1i(id, data); GLERROR
}

template struct Uniform<UniformType::INTEGER>;
template struct Uniform<UniformType::FLOAT>;
template struct Uniform<UniformType::VEC2>;
template struct Uniform<UniformType::VEC3>;
template struct Uniform<UniformType::VEC4>;
template struct Uniform<UniformType::MAT2>;
template struct Uniform<UniformType::MAT3>;
template struct Uniform<UniformType::MAT4>;
template struct Uniform<UniformType::SAMPLER2D>;
