#include "TextObject.hpp"
#include "Debug.hpp"

TextObject::TextObject(
    const char *text,
    size_t font_id,
    gl::ShaderProgram &program,
    glm::vec2 position,
    glm::vec3 color,
    float size
):
  ttext(),
  program(program),
  position(position),
  font_id(font_id),
  color(color),
  size(size)
{
  ttext.SetText(std::string(text));
}

TextObject::~TextObject()
{}

void TextObject::Init() {
  ttext.Init(font_id);
}

void TextObject::SetVisible(bool visible) {
  is_visible = visible;
}

void TextObject::SetText(const char *text) {
  ttext.SetText(std::string(text));
}

void TextObject::SetColor(float x, float y, float z) {
  color = glm::vec3(x, y, z);
}

void TextObject::Draw() {
  if(!is_visible)
    return;
  ttext.Render(program,
              position.x - (ttext.width()*size) / 2,
              position.y - (ttext.height()*size) / 2,
  size, color);
}

void TextObject::Clear() {
  ttext.Clear();
}
