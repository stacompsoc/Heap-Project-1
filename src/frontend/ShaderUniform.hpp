#pragma once

#include <string>
#include <type_traits>
#include <glm/glm.hpp>
#include "incgraphics.h"

enum UniformType {
  FLOAT,
  VEC2, VEC3, VEC4,
  MAT4,
  SAMPLER2D
};

template <UniformType U> struct u_cast_type;
template <> struct u_cast_type <FLOAT> { using type = GLfloat; };
template <> struct u_cast_type <VEC2> { using type = glm::vec2; };
template <> struct u_cast_type <VEC3> { using type = glm::vec3; };
template <> struct u_cast_type <VEC4> { using type = glm::vec4; };
template <> struct u_cast_type <MAT4> { using type = glm::mat4; };
template <> struct u_cast_type <SAMPLER2D> { using type = GLuint; };
template <UniformType U> struct u_cast_type { using type = void; };

template <UniformType U>
struct Uniform {
  using type = typename u_cast_type<U>::type;
  using dtype = std::conditional_t<std::is_fundamental<type>::value,
        std::remove_reference_t<type>, type>;
  GLuint id = 0;
  GLuint prog_id = 0;
  std::string location;
  Uniform(const char *loc);
  ~Uniform();
  void set_id(GLuint program_id);
  GLuint get_id(GLuint program_id = -1u);
  void set_data(const dtype &data);
};
