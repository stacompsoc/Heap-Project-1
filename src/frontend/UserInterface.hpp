#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Screen.hpp"
#include "ShaderProgram.hpp"
#include "ShaderUniform.hpp"
#include "Object.hpp"
#include "TextObject.hpp"
#include "Texture.hpp"

class UserInterface {
protected:
  friend class UIBuilder;
  Screen
    *screen;
  gl::Program
    quadProgram,
    textProgram;
  size_t BCKGR, BTN, BTNSEL;
  std::vector<Object>
    uiObjects;
  std::vector<TextObject>
    uiTexts;
  gl::Uniform<gl::UniformType::MAT4>
    u_proj;
  glm::mat4
    projection_matrix;

  UserInterface(Screen *screen);
  ~UserInterface();
  size_t width();
  size_t height();
  void AddObject(Object &&object);
  void AddQuad(size_t texture_id, glm::vec2 &&pos, glm::vec2 &&scale);
  void AddText(TextObject &&textobj);
  void Init();
  void Clear();
  static UserInterface *instance;
public:
  void Draw();
  static UserInterface *inst();
  static void Setup(Screen *screen);
  static void CleanUp();
};
