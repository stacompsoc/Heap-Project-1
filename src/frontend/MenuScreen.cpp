#include "MenuScreen.hpp"
#include "Storage.hpp"
#include "Window.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

MenuScreen::MenuScreen(Window *win):
  Screen(win),
  quadprogram({"pquad.vert", "pquad.frag"}),
  menuprogram({"ptext.vert", "ptext.frag"}),
  text("Amazing space picture"),
  /* label("Push"), */
  u_proj("projection")
{}

MenuScreen::~MenuScreen()
{}

void MenuScreen::Init() {
  size_t ARIAL = Storage::inst()->AddFont("fonts/Arial.ttf");
  quadprogram.Init({"vposition", "vtexcoords"});
  menuprogram.Init({"vertex"});
  PIC = Storage::inst()->AddTexture("textures/menubackground.tga");
  BTN = Storage::inst()->AddTexture("textures/button.tga");
  BTNSEL = Storage::inst()->AddTexture("textures/button_sel.tga");
  text.Init(ARIAL);
  /* label.Init(ARIAL); */
  projection_matrix = glm::ortho(0.0f, float(width()), 0.0f, float(height()));
  size_t QUAD = 2;
  objects.push_back(
    Object(
      QUAD, quadprogram, PIC,
      1.0f,
      width()/2,height()/2,-.5,
      0
    )
  );
  objects.back().Init();
  objects.back().Rotate(0, 1, 0, 90);
  objects.back().SetScale(width()/2, height()/2, 0);
  /* objects.push_back( */
  /*   Object( */
  /*     QUAD, quadprogram, BTN, */
  /*     0.02f, */
  /*     width()/2,height()/2 + 200,-.3, */
  /*     0 */
  /*   ) */
  /* ); */
  /* objects.back().Init(); */
  /* objects.back().Rotate(0, 1, 0, 90); */
  /* objects.back().SetScale(100, 50, 0); */
}

void MenuScreen::Display() {
  quadprogram.Use();

  u_proj.set_id(quadprogram.id());
  u_proj.set_data(projection_matrix);

  Storage::inst()->textures()[PIC].AttachToShader(quadprogram);
  Storage::inst()->textures()[PIC].Bind();
  objects[0].Draw();
  Texture::Unbind();

  /* Storage::inst()->textures()[BTN].AttachToShader(quadprogram); */
  /* Storage::inst()->textures()[BTN].Bind(); */
  /* objects[1].Draw(); */
  /* Texture::Unbind(); */

  ShaderProgram::Unuse();

  menuprogram.Use();
  u_proj.set_id(menuprogram.id());
  u_proj.set_data(projection_matrix);
  text.Render(menuprogram, width()/2 - 250, height()/2, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
  ShaderProgram::Unuse();
}

void MenuScreen::Keyboard() {
  if(glfwGetKey(win_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win_->window, true);
  } else if(glfwGetKey(win_->window, GLFW_KEY_ENTER) == GLFW_PRESS) {
    should_close = true;
  }
}

void MenuScreen::Mouse(double x, double y) {
}

void MenuScreen::Clear() {
  for(auto &obj : objects) {
    obj.Clear();
  }
  menuprogram.Clear();
  quadprogram.Clear();
}
