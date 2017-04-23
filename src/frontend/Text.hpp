#pragma once

#include <string>

#include "incgraphics.h"
#include "freetype_config.h"
#include "Storage.hpp"
#include "Font.hpp"
#include "ShaderProgram.hpp"

#include <glm/glm.hpp>

class Text {
protected:
  Uniform <VEC3> u_textcolor;
  GLuint vao = 0;
  GLuint vbo = 0;
  std::string text = "";
  size_t font_id = 0;
  GLuint tex = 0;
  size_t width_ = 0, height_ = 0;
public:
  Text();
  ~Text();
  size_t width() const;
  size_t height() const;
  void SetText(std::string &&new_text);
  void Init(size_t fontid);
  void Render(ShaderProgram &program, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 &color);
  void Clear();
};
