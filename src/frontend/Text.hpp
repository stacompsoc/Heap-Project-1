#pragma once

#include <string>
#include <glm/glm.hpp>

#include "incgraphics.h"
#include "freetype_config.h"

#include "Storage.hpp"
#include "Font.hpp"
#include "ShaderProgram.hpp"
#include "VertexArray.hpp"
#include "ShaderAttrib.hpp"

class Text {
protected:
  gl::Uniform<gl::UniformType::VEC3> u_textcolor;
  gl::VertexArray vao;
  gl::Attrib vbo;
  std::string text = "";
  size_t font_id = 0;
  gl::Attrib tex;
  size_t width_ = 0, height_ = 0;
public:
  Text();
  ~Text();
  size_t width() const;
  size_t height() const;
  void SetText(std::string &&new_text);
  void Init(size_t fontid);
  void Render(gl::Program &program, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 &color);
  void Clear();
};
