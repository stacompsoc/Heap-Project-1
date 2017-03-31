#pragma once

#include <string>

#include "incgraphics.h"
#include "freetype_config.h"
#include "Storage.hpp"
#include "Font.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

class Text {
protected:
  GLuint vao = 0;
  GLuint vbo = 0;
  std::string text;
  size_t font_id = 0;
  size_t color_id = 0;
  GLuint tex = 0;
public:
  Text(std::string text);
  ~Text();
  void SetText(std::string &&new_text);
  void Init(size_t fontid, size_t colorid = 0);
  void Render(ShaderProgram &program, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 &&color);
  void Clear();
};
