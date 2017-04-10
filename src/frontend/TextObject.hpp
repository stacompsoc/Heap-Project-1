#pragma once

#include <glm/glm.hpp>

#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Text.hpp"

class TextObject {
protected:
  ShaderProgram &program;
  glm::vec2
    position;
  glm::vec3
    color;
  float
    size;
  Text ttext;
  size_t font_id;
  bool is_visible = true;
public:
  TextObject(
    const char *text,
    size_t font_id,
    ShaderProgram &program,
    glm::vec2 position,
    glm::vec3 color,
    float size
  );
  ~TextObject();
  void Init();
  void SetVisible(bool visible);
  void SetText(const char *text);
  void SetColor(float x, float y, float z);
  void Draw();
  void Clear();
};
