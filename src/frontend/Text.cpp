#include "Text.hpp"
#include "ShaderUniform.hpp"
#include "Log.hpp"

Text::Text(std::string text):
  text(text)
{}

Text::~Text()
{}

void Text::Init(size_t fontid, size_t colorid) {
  font_id = fontid, color_id = colorid;
  glGenVertexArrays(1, &vao); GLERROR
  glGenBuffers(1, &vbo); GLERROR
  glBindVertexArray(vao); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, vbo); GLERROR
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW); GLERROR
  glEnableVertexAttribArray(0); GLERROR
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0); GLERROR
  glBindBuffer(GL_ARRAY_BUFFER, 0); GLERROR
  glBindVertexArray(0); GLERROR
}

void Text::SetText(std::string &&new_text) {
  text = new_text;
}

void Text::Render(ShaderProgram &program, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 &&color) {
  program.Use();
  Uniform<VEC3>u_textcolor("textcolor");
  u_textcolor.set_id(program.id());
  u_textcolor.set_data(color);
  glActiveTexture(GL_TEXTURE0); GLERROR
  glBindVertexArray(vao); GLERROR
  Font &font = Storage::inst()->fonts()[font_id];
  for(const GLchar *c = text.c_str(); *c != '\0'; ++c) {
    Font::Character &ch = font.alphabet[*c];
    GLfloat
      posx = x + ch.bearing.x * scale,
      posy = y - (ch.size.y - ch.bearing.y) * scale;
    GLfloat
      w = ch.size.x * scale,
      h = ch.size.y * scale;
    GLfloat vertices[6][4] = {
      { posx,     posy + h,   0.0, 0.0 },
      { posx,     posy,       0.0, 1.0 },
      { posx + w, posy,       1.0, 1.0 },

      { posx,     posy + h,   0.0, 0.0 },
      { posx + w, posy,       1.0, 1.0 },
      { posx + w, posy + h,   1.0, 0.0 },
    };
    glBindTexture(GL_TEXTURE_2D, ch.tex.tex); GLERROR
    glBindBuffer(GL_ARRAY_BUFFER, vbo); GLERROR
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); GLERROR
    glBindBuffer(GL_ARRAY_BUFFER, 0); GLERROR
    glDrawArrays(GL_TRIANGLES, 0, 6); GLERROR
    x += (ch.advance >> 6) * scale;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0); GLERROR
}

void Text::Clear() {
}
