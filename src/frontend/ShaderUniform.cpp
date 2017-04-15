#include "ShaderUniform.hpp"
#include "Log.hpp"

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
void Uniform<VEC3>::set_data(const Uniform<VEC3>::dtype &data) {
  ASSERT(prog_id != 0);
  glUniform3f(id, data.x, data.y, data.z); GLERROR
}

template <>
void Uniform<MAT4>::set_data(const glm::mat4 &data) {
  ASSERT(prog_id != 0);
  glUniformMatrix4fvARB(id, 1 , GL_FALSE, glm::value_ptr(data)); GLERROR
}

template <>
void Uniform<SAMPLER2D>::set_data(const Uniform<SAMPLER2D>::dtype &data) {
  ASSERT(prog_id != 0);
  glUniform1i(id, data); GLERROR
}

template struct Uniform<SAMPLER2D>;
template struct Uniform<VEC3>;
template struct Uniform<MAT4>;