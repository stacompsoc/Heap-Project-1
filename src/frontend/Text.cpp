#include "Text.hpp"
#include "Debug.hpp"
#include "ShaderUniform.hpp"
#include "Sprite.hpp"

Text::Text():
  u_textcolor("textcolor")
{}

Text::~Text()
{}

void Text::Init(size_t fontid) {
  font_id = fontid;
  vao.Init();
  vao.Bind();
  vbo.Init(GL_ARRAY_BUFFER);
  vbo.Bind();
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW); GLERROR
  vao.Enable(vbo);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0); GLERROR
  gl::Attrib::Unbind<GL_ARRAY_BUFFER>();
  gl::VertexArray::Unbind();
}

size_t Text::width() const {
  return width_;
}

size_t Text::height() const {
  return height_;
}

void Text::SetText(std::string &&new_text) {
  text = new_text;
  width_ = 0, height_ = 0;
  for(const char *c = text.c_str(); *c != '\0'; ++c) {
    Font::Character &ch = Sprite<Font>::Access(font_id).alphabet[*c];
    width_ += ch.size.x + ch.bearing.x,
    height_ += ch.size.y - ch.bearing.y;
  }
}

void Text::Render(gl::ShaderProgram &program, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 &color) {
  program.Use();
  u_textcolor.unset_id();
  u_textcolor.set_id(program.id());
  u_textcolor.set_data(color);
  glActiveTexture(GL_TEXTURE0); GLERROR
  vao.Bind();
  Font &font = Sprite<Font>::Access(font_id);
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
    ch.tex.Bind(gl::Texture::BIND_INDEX_DEFAULT, gl::Texture::BIND_NO_ACTIVATION | gl::Texture::BIND_NO_SET_DATA);
    vbo.Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); GLERROR
    gl::Attrib::Unbind<GL_ARRAY_BUFFER>();
    glDrawArrays(GL_TRIANGLES, 0, 6); GLERROR
    x += (ch.advance >> 6) * scale;
  }
  gl::VertexArray::Unbind();
  gl::Texture::Unbind();
}

void Text::Clear() {
}
