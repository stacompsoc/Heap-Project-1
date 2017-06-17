#pragma once

#include <string>
#include <type_traits>
#include <glm/glm.hpp>
#include "incgraphics.h"

enum class UniformType {
  INTEGER, FLOAT,
  VEC2, VEC3, VEC4,
  MAT2, MAT3, MAT4,
  SAMPLER2D
};

template <UniformType U> struct u_cast_type;
template <> struct u_cast_type <UniformType::INTEGER> { using type = GLfloat; };
template <> struct u_cast_type <UniformType::FLOAT> { using type = GLfloat; };
template <> struct u_cast_type <UniformType::VEC2> { using type = glm::vec2; };
template <> struct u_cast_type <UniformType::VEC3> { using type = glm::vec3; };
template <> struct u_cast_type <UniformType::VEC4> { using type = glm::vec4; };
template <> struct u_cast_type <UniformType::MAT2> { using type = glm::mat2; };
template <> struct u_cast_type <UniformType::MAT3> { using type = glm::mat3; };
template <> struct u_cast_type <UniformType::MAT4> { using type = glm::mat4; };
template <> struct u_cast_type <UniformType::SAMPLER2D> { using type = GLuint; };
template <UniformType U> struct u_cast_type { using type = void; };

template <UniformType U>
struct Uniform {
  using type = typename u_cast_type<U>::type;
  using dtype = std::conditional_t<std::is_fundamental<type>::value,
        std::remove_reference_t<type>, std::add_const_t<std::add_lvalue_reference_t<type>>>;
  GLuint id = 0;
  GLuint prog_id = 0;
  std::string location;
  Uniform(const char *loc);
  ~Uniform();
  void set_id(GLuint program_id);
  void unset_id();
  GLuint get_id(GLuint program_id = -1u);
  void set_data(dtype data);
};
